#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-15;
const int mod = 998244353;
const int mod1 = 999999937;
const int INF = 2e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, x;
    cin >> n >> x;
    int s = 12345;
    vector<bool> erat(100000), block(s);
    vector<int> primes(100000);
    int cnt = 0;
    int root = (int)sqrt(n + .0);
    for (int i = 2; i <= root; i++) {
        if (!erat[i]) {
            primes[cnt++] = i;
            if (i * 1ll * i <= root) {
                for (int j = i * i; j <= root; j += i) {
                    erat[j] = true;
                }
            }
        }
    }
    int h = 0;
    int cur = 0;
    for (int k = 0, maxk = n / s; k <= maxk; k++) {
        fill(block.begin(), block.end(), false);
        int start = k * s;
        for (int i = 0; i < cnt; i++) {
            int start_idx = (start + primes[i] - 1) / primes[i];
            for (int j = max(start_idx, 2) * primes[i] - start; j < s; j += primes[i]) {
                block[j] = true;
            }
        }
        if (k == 0) {
            block[0] = block[1] = true;
        }
        for (int i = 0; i < s && start + i <= n; i++) {
            if (!block[i]) {
                h = h * x + cur;
            }
            cur++;
        }
    }
    cout << h;
    return 0;
}
