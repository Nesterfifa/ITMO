#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 1e9;
const ll INFLL = 3e18;

vector<vector<int> > g(100000);
int up[100000][18];
int t_in[100000], t_out[100000], deep[100000];
int timer = 0;

void dfs(int v, int p = 0) {
    if (p != -1) {
        deep[v] = deep[p] + 1;
    }
    t_in[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < 18; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto u : g[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
    t_out[v] = timer++;
}

bool is_ancestor(int a, int b) {
    return t_in[a] <= t_in[b] && t_out[a] >= t_out[b];
}

int lca(int a, int b) {
    if (is_ancestor(a, b)) {
        return a;
    }
    if (is_ancestor(b, a)) {
        return b;
    }
    for (int i = 17; i >= 0; i--) {
        if (!is_ancestor(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        g[x].pb(i);
        g[i].pb(x);
    }
    dfs(0);
    vector<int> a(2 * m);
    int x, y, z;
    cin >> a[0] >> a[1] >> x >> y >> z;
    for (int i = 2; i < 2 * m; i++) {
        a[i] = (int)(((ll)a[i - 2] * (ll)x + (ll)a[i - 1] * (ll)y + (ll)z) % (ll)n);
    }
    int v = a[0], u = a[1];
    ll sum = 0;
    for (int t = 1; t <= m; t++) {
        int ans = lca(u, v);
        sum += ans;
        u = a[2 * t + 1];
        v = (a[2 * t] + ans) % n;
    }
    cout << sum;
}
