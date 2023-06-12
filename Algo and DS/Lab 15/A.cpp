#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 998244353;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 6e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, w;
    cin >> n;
    vector<int> a(n);
    for (auto &c : a) {
        cin >> c;
    }
    cin >> w;
    vector<ll> ws;
    for (int t = 0; t < (1 << n / 2); t++) {
        ll sum = 0;
        for (int i = 0; i < n / 2; i++) {
            if (t & (1 << i)) {
                sum += a[i];
            }
        }
        ws.pb(sum);
    }
    ll ans = 0;
    sort(ws.begin(), ws.end());
    for (int t = 0; t < (1 << (n - n / 2)); t++) {
        ll sum = 0;
        for (int i = 0; i < n - n / 2; i++) {
            if (t & (1 << i)) {
                sum += a[i + n / 2];
            }
        }
        ans += upper_bound(ws.begin(), ws.end(), w - sum) - ws.begin();
    }
    cout << ans;
    return 0;
}
