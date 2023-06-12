#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>

// struct which stores matrices and provides operations on them
struct matrix {
    size_t n, m;
    std::vector<std::vector<bool> > data;
    std::vector<std::pair<size_t, size_t> > active; // active segments

    matrix(size_t n, size_t m): n(n), m(m), data(std::vector(n, std::vector<bool>(m))) {}

    // read matrix from the stream
    friend std::istream& operator>>(std::istream &in, matrix &input) {
        int x;
        for (int i = 0; i < input.n; i++) {
            for (int j = 0; j < input.m; j++) {
                in >> x;
                input[i][j] = x == 1;
            }
        }
        return in;
    }

    std::vector<bool>& operator[](int index) {
        return data[index];
    }

    std::vector<bool> const& operator[](int index) const {
        return data[index];
    }

    // transforms matrix to MSF and calculates active segments
    void to_minimal_span_form() {
        gauss_down();
        gauss_up();

        for (int i = 0; i < n; i++) {
            int l = -1, r = -1;
            for (int j = 0; j < m; j++) {
                if (data[i][j]) {
                    r = j;
                    if (l == -1) {
                        l = j;
                    }
                }
            }
            active.emplace_back(l, r);
        }
    }

    // matrix multiplication
    static matrix multiply(matrix const& a, matrix const& b) {
        matrix c(a.n, b.m);

        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < a.m; j++) {
                for (int k = 0; k < b.m; k++) {
                    c[i][k] = c[i][k] ^ (a[i][j] & b[j][k]);
                }
            }
        }

        return c;
    }

private:

    // gauss down operation to make active starts distinct and sort them
    void gauss_down() {
        int column = (int) -1;
        for (size_t target_row = 0; target_row < n; target_row++) {
            column++;
            bool isClear = true;
            if (!data[target_row][column]) { // if diagonal bit is zero, find a row with 1 in this column and do ^=
                isClear = false;
                for (size_t row = target_row + 1; row < n; row++) {
                    if (data[row][column]) {
                        for (size_t i = 0; i < m; i++) {
                            data[target_row][i] = data[target_row][i] ^ data[row][i];
                        }
                        isClear = true;
                        break;
                    }
                }
            }

            // guarantee that we have only one "1" in this column
            // data[row] ^= data[target_row] for all row = target_row+1..n
            if (isClear) {
                for (size_t row = target_row + 1; row < n; row++) {
                    if (data[row][column]) {
                        for (size_t i = 0; i < m; i++) {
                            data[row][i] = data[target_row][i] ^ data[row][i];
                        }
                    }
                }
            } else {
                target_row--; // if there are no "1" in the column, skip the column
            }
        }
    }

    // sort of gauss up operation to make active endings distinct
    void gauss_up() {
        std::vector<bool> free(n, true); // rows that are modified
        size_t column = m; // go from the rows ends
        for (size_t step = 0; step < n; step++) {
            int count = 0; // how many "1" are in the column (excluding modified rows)
            column--;
            for (size_t i = 0; i < n; i++) {
                if (free[i] && data[i][column]) {
                    count++;
                }
            }
            if (count > 0) {
                size_t last = n - 1;
                while (!(data[last][column] && free[last])) {
                    last--;
                }
                free[last] = false;
                if (count > 1) {
                    for (size_t i = 0; i < last; i++) {
                        if (data[i][column] && free[i]) {
                            for (int j = 0; j < m; j++) {
                                data[i][j] = data[last][j] ^ data[i][j];
                            }
                        }
                    }
                }
            } else {
                step--; // if there are no "1" in the column, skip it
            }
        }
    }
};

// node for Viterbi graph
struct node {
    node* zero = nullptr; // node by 0 edge
    node* one = nullptr; // node by 1 edge
    int pattern = 0; // bitmask for information symbols values
    std::vector<int> active_on_layer; // indices of active rows

    node() = default;

    node(int pattern, std::vector<int> active_on_layer): pattern(pattern), active_on_layer(std::move(active_on_layer)) {}
};

// trellis for Viterbi algorithm
struct trellis {
    node* start = nullptr;
    std::vector<std::vector<node*> > layers;

    // build trellis from matrix in MSF
    explicit trellis(matrix const& source): start(new node()), layers(std::vector(source.m + 1, std::vector<node*>())) {
        layers[0].emplace_back(start); // first layer has only start node
        for (int i = 0; i < source.m; i++) {
            std::vector<int> active_rows;
            for (int j = 0; j < source.n; j++) {
                if (source.active[j].first <= i && i < source.active[j].second) {
                    active_rows.emplace_back(j);
                }
            }
            for (int j = 0; j < (1 << active_rows.size()); j++) {
                layers[i + 1].emplace_back(new node(j, active_rows));
            }
        }

        layers[0][0]->zero = layers[1][0];
        layers[0][0]->one = layers[1][1];

        for (int i = 1; i < source.m; i++) {
            for (int j = 0; j < layers[i].size(); j++) {
                int next_index = 0; // fixed bits of number of the connected node on next layer
                int bruteforce_index = -1; // variable bit of the connected node
                int l = 0, r = 0;
                // find intersection of active rows to fix the matching bits and find variable index
                // using two pointers
                while (l < layers[i][0]->active_on_layer.size() || r < layers[i + 1][0]->active_on_layer.size()) {
                    if (r == layers[i + 1][0]->active_on_layer.size()) {
                        l++;
                    } else if (l == layers[i][0]->active_on_layer.size()) {
                        bruteforce_index = r++;
                    } else if (layers[i + 1][0]->active_on_layer[r] == layers[i][0]->active_on_layer[l]) {
                        if ((layers[i][j]->pattern & (1 << l)) > 0) {
                            next_index |= 1 << r;
                        }
                        r++;
                    } else if (layers[i + 1][0]->active_on_layer[r] > layers[i][0]->active_on_layer[l]) {
                        l++;
                    } else {
                        bruteforce_index = r++;
                    }
                }

                // calculate bit on edge
                bool scalar_product = false;
                for (int row = 0; row < layers[i][0]->active_on_layer.size(); row++) {
                    int pattern = layers[i][j]->pattern;
                    int row_index = layers[i][0]->active_on_layer[row];
                    scalar_product ^= ((pattern & (1 << row)) > 0) & source[row_index][i];
                }
                for (int row = 0; row < layers[i + 1][0]->active_on_layer.size(); row++) {
                    int pattern = layers[i + 1][next_index]->pattern;
                    int row_index = layers[i + 1][0]->active_on_layer[row];
                    if (!(source.active[row_index].first <= i - 1 && i - 1 < source.active[row_index].second)) {
                        scalar_product ^= ((layers[i + 1][next_index]->pattern & (1 << row))) & source[row_index][i];
                    }
                }

                if (!scalar_product) {
                    if (bruteforce_index == -1) {
                        layers[i][j]->zero = layers[i + 1][next_index];
                    } else {
                        layers[i][j]->zero = layers[i + 1][next_index];
                        layers[i][j]->one = layers[i + 1][next_index | (1 << bruteforce_index)];
                    }
                } else {
                    if (bruteforce_index == -1) {
                        layers[i][j]->one = layers[i + 1][next_index];
                    } else {
                        layers[i][j]->one = layers[i + 1][next_index];
                        layers[i][j]->zero = layers[i + 1][next_index | (1 << bruteforce_index)];
                    }
                }
            }
        }
    }
};

// decode provided vector using dynamic programming on trellis
std::vector<bool> decode(std::vector<double> const &v, trellis const &t) {
    std::vector<std::vector<double> > dp(t.layers.size());
    std::vector<std::vector<int> > parent(t.layers.size());
    for (int i = 0; i < t.layers.size(); i++) {
        dp[i].resize(t.layers[i].size(), -1e14);
        parent[i].resize(t.layers[i].size(), -1);
    }
    dp[0][0] = 0;
    for (int i = 0; i < t.layers.size() - 1; i++) {
        for (int j = 0; j < t.layers[i].size(); j++) {
            if (t.layers[i][j]->zero != nullptr) {
                double dist = v[i];
                if (dp[i + 1][t.layers[i][j]->zero->pattern] < dp[i][j] + dist) {
                    dp[i + 1][t.layers[i][j]->zero->pattern] = dp[i][j] + dist;
                    parent[i + 1][t.layers[i][j]->zero->pattern] = j;
                }
            }
            if (t.layers[i][j]->one != nullptr) {
                double dist = -v[i];
                if (dp[i + 1][t.layers[i][j]->one->pattern] < dp[i][j] + dist) {
                    dp[i + 1][t.layers[i][j]->one->pattern] = dp[i][j] + dist;
                    parent[i + 1][t.layers[i][j]->one->pattern] = j;
                }
            }
        }
    }
    std::vector<bool> ans;
    int index = 0;
    for (int i = dp.size() - 1; i > 0; i--) {
        node* prev = t.layers[i - 1][parent[i][index]];
        ans.emplace_back(!(prev->zero != nullptr && prev->zero->pattern == index));
        index = prev->pattern;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    std::ifstream cin("input.txt");
    std::ofstream cout("output.txt");
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);


    int n, m;
    cin >> m >> n;
    matrix a(n, m);
    cin >> a;
    matrix min_span = a;
    min_span.to_minimal_span_form();
    trellis t(min_span);
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<std::mt19937::result_type> random_uniform(0, 1);

    for (auto & layer : t.layers) {
        cout << layer.size() << " ";
    }
    cout << "\n";

    std::string command;
    while (cin >> command) {
        if (command == "Encode") {
            matrix input(1, n);
            cin >> input;
            // to encode vector, we multiply it by the generator matrix (definition of the generator matrix)
            matrix result = matrix::multiply(input, a);
            for (int i = 0; i < m; i++) {
                cout << result[0][i] << " ";
            }
            cout << "\n";
        } else if (command == "Decode") {
            std::vector<double> input(m);
            for (int i = 0; i < m; i++) {
                cin >> input[i];
            }
            std::vector<bool> ans = decode(input, t);
            for (int i = 0; i < m; i++) {
                cout << ans[i] << " ";
            }
            cout << "\n";
        } else {
            int noise, iterations, max_errors;
            cin >> noise >> iterations >> max_errors;
            int count_wrong = 0;
            int current_iterations = iterations;
            std::normal_distribution<> normalDistribution(0, std::sqrt(
                    0.5 * pow(10, ((double) -noise) / 10) * ((double) m / n)));
            matrix input(1, n);
            for (int iteration = 0; iteration < iterations; iteration++) {
                for (int j = 0; j < n; j++) {
                    input[0][j] = random_uniform(gen) > 0.5; // generate random vector
                }
                matrix encoded = matrix::multiply(input, a); // encode random vector
                std::vector<double> encoded_noised(m);
                for (int j = 0; j < m; j++) {
                    encoded_noised[j] = (1 - 2 * (encoded[0][j] ? 1 : 0)) + normalDistribution(gen); // add noise
                }
                std::vector<bool> decoded = decode(encoded_noised, t); // decode noised vector
                bool isError = false;
                for (int j = 0; j < n; j++) {
                    if (encoded[0][j] != decoded[j]) {
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
