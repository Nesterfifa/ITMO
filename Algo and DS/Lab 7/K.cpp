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

vector<vector<int> > g(500000);
int up[500000][20];
int t_in[500000], t_out[500000], deep[500000];
int timer = 0;

void dfs(int v, int p = 0) {
    if (p != -1) {
        deep[v] = deep[p] + 1;
    }
    t_in[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < 20; i++) {
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
    for (int i = 19; i >= 0; i--) {
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

    int q;
    cin >> q;
    vector<pair<int, int> > req;
    for (int i = 0; i < q; i++) {
        string s; int a, b;
        cin >> s >> a >> b;
        a--; b--;
        if (s == "ADD") {
            g[a].pb(b);
            g[b].pb(a);
        } else {
            req.pb({a, b});
        }
    }
    dfs(0);
    for (uint i = 0; i < req.size(); i++) {
        cout << lca(req[i].x, req[i].y) + 1 << endl;
    }
    return 0;
}
