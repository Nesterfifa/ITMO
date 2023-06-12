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

struct edge {
    int a, b;
    int c, f;

    edge(int a, int b, int c): a(a), b(b), c(c), f(0) {}
};

vector<edge> edges;
vector<int> q(500);
vector<vector<int> > g;
vector<int> p, d;
int n, m;

bool bfs() {
    fill(d.begin(), d.end(), INF);
    d[0] = 0;
    int l = 0, r = 0;
    q[r++] = 0;
    while (r > l && d[n - 1] == INF) {
        int v = q[l++];
        for (auto u : g[v]) {
            int to = edges[u].b;
            if (d[to] == INF && edges[u].f < edges[u].c) {
                q[r++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[n - 1] != INF;
}

int dfs(int u, int minC) {
    if (u == n - 1 || minC == 0) {
        return minC;
    }
    for (int v = p[u]; v < (int)g[u].size(); v++) {
        int idx = g[u][v], to = edges[idx].b;
        if (d[to] == d[u] + 1) {
            int delta = dfs(to, min(minC, edges[idx].c - edges[idx].f));
            if (delta) {
                edges[idx].f += delta;
                edges[idx ^ 1].f -= delta;
                return delta;
            }
        }
        p[u]++;
    }
    return 0;
}

ll dinic() {
    ll ans = 0;
    while (bfs()) {
        fill(p.begin(), p.end(), 0);
        int flow = dfs(0, INF);
        while (flow != 0) {
            ans += flow;
            flow = dfs(0, INF);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    p.resize(n);
    d.resize(n);
    g.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        x--; y--;

        g[x].pb((int) edges.size());
        edges.pb(edge(x, y, c));
        g[y].pb((int) edges.size());
        edges.pb(edge(y, x, 0));
    }
    cout << dinic();
    return 0;
}
