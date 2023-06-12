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

    int n;
    cin >> n;

    vector<int> lp(1000001);
    vector<int> primes;
    for (int i = 2; i <= 1000000; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.pb(i);
        }
        for (int j = 0; j < (int)primes.size() && primes[j] <= lp[i] && i * primes[j] <= 1000000; j++)
            lp[i * primes[j]] = primes[j];
    }

    while (n--) {
        int x;
        cin >> x;
        while (x > 1) {
            cout << lp[x] << " ";
            x /= lp[x];
        }
        cout << "\n";
    }
    return 0;
}
