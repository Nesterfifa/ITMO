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
const int INF = 2e9 + 500;
const ll INFLL = 3e18;

vector<vector<pair<int, int> > > g;
vector<int> d, topsort, used;

void dfs(int v) {
    used[v] = true;
    for (auto u : g[v]) {
        if (!used[u.x]) {
            dfs(u.x);
        }
    }
    topsort.pb(v);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;

    d.resize(n, INF);
    g.resize(n);
    used.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--; y--;
        g[x].pb({y, w});
    }
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    for (int i = 0; i < n; i++) {
        for (auto v : g[topsort[i]]) {
            d[v.first] = min(d[v.first], d[topsort[i]] + v.second);
        }
    }
    if (d[t] < 1e9) {
        cout << d[t];
    } else {
        cout << "Unreachable";
    }
    return 0;
}
