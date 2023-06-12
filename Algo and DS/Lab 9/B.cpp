#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define x first
#define y second

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 3e18;

vector<vector<pair<int, ll> > > g;
vector<ll> d;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, s, t;
    cin >> n >> s >> t;
    s--; t--;

    g.resize(n);
    d.resize(n, INFLL);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll x;
            cin >> x;
            if (x != -1 && i != j) {
                g[i].pb({j, x});
            }
        }
    }
    d[s] = 0;
    set<pair<int, int> > q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto u : g[v]) {
            if (d[v] + u.y < d[u.x]) {
                q.erase({d[u.x], u.x});
                d[u.x] = d[v] + u.y;
                q.insert({d[u.x], u.x});
            }
        }
    }
    if (d[t] != INFLL) {
        cout << d[t];
    } else {
        cout << -1;
    }
    return 0;
}
