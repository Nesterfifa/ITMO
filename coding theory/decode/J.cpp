#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>

// calculate the remainder of bitmask polynomial a divided by b
int pol_mod(int a, int b) {
    int deg = -1;
    for (int i = 31; i >= 0; i--) {
        if ((b & (1 << i)) > 0) {
            deg = i;
            break;
        }
    }

    for (int i = 31; i >= deg; i--) {
        if ((a & (1 << i)) > 0) {
            a ^= b << (i - deg);
        }
    }

    return a;
}

// shift polynomial vector by r
std::vector<int> vector_shift(std::vector<int> const& v, int r) {
    std::vector<int> res(v.size());
    for (int i = v.size(); i >= r; i--) {
        res[i] = v[i - r];
    }
    return res;
}

// xor two polynomial vectors
std::vector<int> vector_xor(std::vector<int> const& a, std::vector<int> const& b) {
    std::vector<int> c(a.size());
    for (int i = 0; i < b.size(); i++) {
        c[i] = a[i] ^ b[i];
    }
    return c;
}

// polynomial multiplication
std::vector<int> vector_multiply(std::vector<int> const& a, std::vector<int> const& b) {
    std::vector<int> c(a.size());
    for (int i = 0; i < b.size(); i++) {
        if (b[i] > 0) {
            std::vector<int> shifted = vector_shift(a, i);
            for (int j = 0; j < a.size(); j++) {
                c[j] ^= shifted[j];
            }
        }
    }
    return c;
}

// remainder of polynomial a divided by b
std::vector<int> vector_mod(std::vector<int> const& a, std::vector<int> const& b) {
    std::vector<int> c(a);
    int deg = -1;
    for (int i = 0; i < b.size(); i++) {
        if (b[i] > 0) {
            deg = i;
        }
    }

    for (int i = c.size() - 1; i >= deg; i--) {
        if (c[i] > 0) {
            std::vector<int> shifted = vector_shift(b, i - deg);
            for (int j = 0; j < b.size(); j++) {
                c[j] ^= shifted[j];
            }
        }
    }
    return c;
}

// encode vector using the formula 'c(x) = v(x) * x^r + x^r * v(x) mod g(x)'
std::vector<int> encode(std::vector<int> const& v, std::vector<int> const& gen_pol, int r) {
    std::vector<int> shifted = vector_shift(v, r);
    return vector_xor(shifted, vector_mod(shifted, gen_pol));
}

// decode vector using Berlekamp-Massey algorithm
std::vector<int> decode(
        std::vector<int> &v,
        std::vector<int> &alpha,
        std::unordered_map<int, int> &alpha_to_power,
        int d,
        int n
) {
    int l = 0; // current length of register
    std::vector<int> loc{1}; // locators polynomial
    std::vector<int> b{1}; // residual compensation polynomial

    std::vector<int> s(d); // syndrome polynomials
    for (int i = 1; i < d; i++) {
        for (int j = 0; j < n; j++) {
            if (v[j] > 0) {
                s[i] ^= alpha[(i * j) % n];
            }
        }
    }

    int b_start = 0;
    for (int i = 1; i < d; i++) {
        b.emplace_back(0); // shift B
        if (i % 2 == 0) {
            continue;
        }
        int delta = 0; // residual
        for (int j = 0; j <= l; j++) {
            if (s[i - j] > 0 && loc[j] > 0) {
                delta ^= alpha[(alpha_to_power[loc[j]] + alpha_to_power[s[i - j]]) % n]; // delta = sum[0;l]{/\_j * S_{i - j}}
            }
        }

        if (delta != 0) { // if we have residual, we change the locator coefficients
            std::vector<int> t(std::max(loc.size(), b.size() - b_start));
            for (int j = 0; j < t.size(); j++) {
                if (j >= b.size() - b_start || j < b.size() - b_start && b[b.size() - 1 - j] == 0) {
                    t[j] = j < loc.size() ? loc[j] : 0;
                } else {
                    t[j] = (j < loc.size() ? loc[j] : 0) ^ alpha[(alpha_to_power[delta] + alpha_to_power[b[b.size() - 1 - j]]) % n];
                }
            }
            if (2 * l <= i - 1) {
                for (int j = b_start; j < b.size(); j++) {
                    if (j - b_start >= loc.size() || j - b_start < loc.size() && loc[j - b_start] == 0) {
                        b[b.size() - 1 - j + b_start] = 0;
                    } else {
                        b[b.size() - 1 - j + b_start] = alpha[(alpha_to_power[loc[j - b_start]] + n - alpha_to_power[delta]) % n];
                    }
                }
                l = i - l;
            }
            loc = t;
            while (b_start < b.size() && b[b_start] == 0) {
                b_start++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int loc_ai = 0;
        for (int j = 0; j < loc.size(); j++) {
            if (loc[j] > 0) {
                loc_ai ^= alpha[(alpha_to_power[loc[j]] + (n - i) * j % n) % n];
            }
        }
        if (loc_ai == 0) { // if /\(alpha^-i) = 0 then we have to correct the symbol
            v[i] ^= 1;
        }
    }

    return v;
}

int main() {
    std::ifstream cin("input.txt");
    std::ofstream cout("output.txt");
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, p, d;
    cin >> n >> p >> d;

    std::vector<int> alpha(n, 1); // alpha int the power of i
    std::unordered_map<int, int> alpha_to_power; // alpha^i -> i
    alpha_to_power[1] = 0;

    for (int i = 1; i < n; i++) {
        alpha[i] = pol_mod(alpha[i - 1] << 1, p);
        alpha_to_power[alpha[i]] = i;
    }

    std::unordered_map<int, std::vector<int> > c; // cyclotomic classes
    std::vector<bool> used(n);
    for (int i = 1; i < d; i++) {
        if (used[i]) {
            continue;
        }

        int i2 = i;
        while (true) {
            i2 *= 2;
            i2 %= n;
            c[i].emplace_back(i2);
            used[i2] = true;
            if (i2 == i) {
                break;
            }
        }
    }

    std::vector<int> gen_pol{1}; // generative polynomial
    gen_pol.resize(256);
    int r = 0;
    for (int i = 1; i <= d - 1; i++) {
        if (c.count(i) == 0) {
            continue;
        }

        int sz = c[i].size();
        r += sz;
        std::vector<int> pol(256); // minimal polynomial for c_i
        for (int mask = 0; mask < (1ull << sz); mask++) { // mask to calculate the coefficient by x^i
            size_t x_deg = 0;
            int alpha_term = 1;
            for (size_t deg = 0; deg < sz; deg++) {
                if ((mask & (1ull << deg)) > 0) { // mask_deg: 0 -> x, 1 -> alpha_deg
                    alpha_term = alpha[(alpha_to_power[alpha_term] + c[i][deg]) % n];
                } else {
                    x_deg++;
                }
            }
            pol[x_deg] ^= alpha_term;
        }

        gen_pol = vector_multiply(gen_pol, pol); // g(x) = \prod[i=1..d-1]{M_i(x)}
    }
    long long k = n - r;
    cout << k << "\n";
    for (int i = 0; i <= r; i++) {
        cout << gen_pol[i] << " ";
    }
    cout << "\n";

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int> random_uniform(0, 1);
    std::uniform_int_distribution<int> random_uniform_noise(0, 100000);

    std::string command;
    while (cin >> command) {
        if (command == "Encode") {
            std::vector<int> input(256);
            for (int i = 0; i < k; i++) {
                cin >> input[i];
            }
            std::vector<int> result = encode(input, gen_pol, r);
            for (int i = 0; i < n; i++) {
                cout << result[i] << " ";
            }
            cout << "\n";
        } else if (command == "Decode") {
            std::vector<int> input(256);
            for (int i = 0; i < n; i++) {
                cin >> input[i];
            }
            std::vector<int> result = decode(input, alpha, alpha_to_power, d, n);
            for (int i = 0; i < n; i++) {
                cout << result[i] << " ";
            }
            cout << "\n";
        } else {
            int iterations, max_errors;
            double noise;
            cin >> noise >> iterations >> max_errors;
            int count_wrong = 0;
            int current_iterations = iterations;
            for (int iteration = 0; iteration < iterations; iteration++) {
                std::vector<int> input(256);
                for (int i = 0; i < k; i++) {
                    input[i] = random_uniform(gen);
                }
                std::vector<int> encoded = encode(input, gen_pol, r);
                std::vector<int> encoded_noised = encoded;
                for (int j = 0; j < n; j++) {
                    if (random_uniform_noise(gen) < 100000 * noise) {
                        encoded_noised[j] ^= 1;
                    }
                }
                std::vector<int> decoded = decode(encoded_noised, alpha, alpha_to_power, d, n);
                bool isError = false;
                for (int j = 0; j < n; j++) {
                    if (decoded[j] != encoded[j]) {
                        isError = true;
                        break;
                    }
                }
                if (isError) {
                    count_wrong++;
                }
                if (count_wrong >= max_errors) {
                    current_iterations = iteration + 1;
                    break;
                }
            }
            cout << std::fixed << (double) count_wrong / current_iterations << '\n';
        }
    }

    return 0;
}