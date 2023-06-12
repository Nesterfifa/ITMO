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

vector<vector<ll> > c, f;
vector<int> p, d;
int n, m;

bool bfs() {
    fill(d.begin(), d.end(), INF);
    d[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (f[u][v] < c[u][v] && d[v] == INF) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[n - 1] != INF;
}

ll dfs(int u, ll minC) {
    if (u == n - 1 || minC == 0) {
        return minC;
    }
    for (int v = p[u]; v < n; v++) {
        if (d[v] == d[u] + 1) {
            ll delta = dfs(v, min(minC, c[u][v] - f[u][v]));
            if (delta) {
                f[u][v] += delta;
                f[v][u] -= delta;
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
        ll flow = dfs(0, INF);
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

    c.resize(n, vector<ll>(n));
    f.resize(n, vector<ll>(n));
    p.resize(n);
    d.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y, cap;
        cin >> x >> y >> cap;
        x--; y--;
        c[x][y] = cap;
    }
    cout << dinic();
    return 0;
}
