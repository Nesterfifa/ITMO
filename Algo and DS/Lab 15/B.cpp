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

    string s;
    cin >> s;
    int n = s.size() / 2;
    unordered_map<string, int> subs;
    for (int t = 0; t < (1 << n); t++) {
        string x = "", y = "";
        for (int i = 0; i < n; i++) {
            if (t & (1 << i)) {
                y.pb(s[i]);
            } else {
                x.pb(s[i]);
            }
        }
        int m = min(x.size(), y.size());
        if (x.substr(0, m) == y.substr(0, m) && x.size() >= y.size()) {
            subs[x.substr(m)]++;
        }
    }
    ll ans = 0;
    for (int t = 0; t < (1 << n); t++) {
        string x, y;
        for (int i = 0; i < n; i++) {
            if (t & (1 << i)) {
                y.pb(s[i + n]);
            } else {
                x.pb(s[i + n]);
            }
        }
        int m = min(x.size(), y.size());
        for (int i = 0; i < m; i++) {
            if (x[x.size() - i - 1] != y[y.size() - i - 1]) {
                x = y = "";
                break;
            }
        }
        if (x == "" && y == "") {
            continue;
        }
        if (x.size() > y.size()) {
            ans += subs[x.substr(0, x.size() - m)];
        } else {
            ans += subs[y.substr(0, y.size() - m)];
        }
    }
    cout << ans;
    return 0;
}
