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

    int n, s = 0, m;
    cin >> n >> m;

    g.resize(n);
    d.resize(n, INFLL);

    for (int i = 0; i < m; i++) {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        x--; y--;
        g[x].pb({y, w});
        g[y].pb({x, w});
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
    for (auto u : d) {
        cout << u << ' ';
    }
    return 0;
}
