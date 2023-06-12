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
const int INF = 1e9;
const ll INFLL = 3e18;

pair<int, int> up[200000 + 13][20];
vector<vector<pair<int, int> > > g;
vector<int> tin, tout, d;
int t;

void dfs(int v, int p = 0) {
    if (v != 0) {
        d[v] = d[p] + 1;
    }
    up[v][0].first = p;
    tin[v] = t++;
    for (int i = 1; i < 20; i++) {
        up[v][i].first = up[up[v][i - 1].first][i - 1].first;
        up[v][i].second = min(up[v][i - 1].second, up[up[v][i - 1].first][i - 1].second);
    }
    for (size_t i = 0; i < g[v].size(); i++) {
        int to = g[v][i].first;
        if (to != p) {
            up[to][0].second = g[v][i].second;
            dfs(to, v);
        }
    }
    tout[v] = t++;
}

bool ancestor(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ancestor(a, b)) {
        return a;
    }
    if (ancestor(b, a)) {
        return b;
    }
    for (int i = 19; i >= 0; i--) {
        if (!ancestor(up[a][i].first, b)) {
            a = up[a][i].first;
        }
    }
    return up[a][0].first;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    g.resize(n);
    tin.resize(n);
    tout.resize(n);
    d.resize(n, 0);

    for (int i = 1; i < n; i++) {
        int x, w;
        cin >> x >> w;
        x--;
        g[x].pb({i, w});
        g[i].pb({x, w});
    }
    for (int i = 0; i < 20; i++) {
        up[0][i].second = 1000000000;
    }
    dfs(0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        int v = lca(a, b);
        int ans = 1000000000;
        for (int j = 19; j >= 0; j--) {
            if (d[up[a][j].first] >= d[v]) {
                ans = min(up[a][j].second, ans);
                a = up[a][j].first;
            }
        }
        for (int j = 19; j >= 0; j--) {
            if (d[up[b][j].first] >= d[v]) {
                ans = min(up[b][j].second, ans);
                b = up[b][j].first;
            }
        }
        cout << ans << endl;
    }
}
