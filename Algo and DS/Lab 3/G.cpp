#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define ins insert

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 1e9 + 9;
const int INF = 1e9;
const ll INFLL = 3e18;

vector<int> p(300006);

int leader(int v) {
    return p[v] == v ? v : p[v] = leader(p[v]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n + 5; i++) {
        p[i] = i;
    }
    vector<int> ans(n + 5, -(1ll << 31));
    vector<pair<int, pair<int, int> > > req(m);
    while (m--) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        req[m] = make_pair(x, make_pair(l, r));
    }
    sort(req.rbegin(), req.rend());
    for (uint i = 0; i < req.size(); i++) {
        int l = req[i].second.first, r = req[i].second.second, x = req[i].first;
        while (l <= r) {
            l = leader(l);
            if (l > r) {
                break;
            }
            ans[l] = x;
            p[l] = leader(l + 1);
        }
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
    return 0;
}
