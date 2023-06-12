#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 6e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string p, s;
    cin >> p >> s;
    string ps = p + "#" + s;
    int n = (int)ps.size();

    vector<int> ps_z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            ps_z[i] = min(ps_z[i - l], r - i + 1);
        }
        while (i + ps_z[i] < n && ps[ps_z[i]] == ps[i + ps_z[i]]) {
            ps_z[i]++;
        }
        if (i + ps_z[i] - 1 > r) {
            l = i;
            r = i + ps_z[i] - 1;
        }
    }

    reverse(p.begin(), p.end());
    reverse(s.begin(), s.end());

    string sp = p + "#" + s;
    vector<int> sp_z(n);
    l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            sp_z[i] = min(sp_z[i - l], r - i + 1);
        }
        while (i + sp_z[i] < n && sp[sp_z[i]] == sp[i + sp_z[i]]) {
            sp_z[i]++;
        }
        if (i + sp_z[i] - 1 > r) {
            l = i;
            r = i + sp_z[i] - 1;
        }
    }

    vector<int> ans;
    int m = p.size();
    for (int i = m + 1; i < n - m + 1; i++) {
        int pos = i - m - 1;
        if (ps_z[i] == m || ps_z[i] + sp_z[n - pos - m] == m - 1) {
            ans.pb(pos + 1);
        }
    }
    cout << ans.size() << endl;
    for (auto u : ans) {
        cout << u << " ";
    }
    return 0;
}
