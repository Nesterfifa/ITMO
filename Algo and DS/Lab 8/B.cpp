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

vector<vector<int> > g, rev_g;
vector<int> used, order, color;
int c;

void dfs(int v) {
    used[v] = true;
    for (auto u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    order.pb(v);
}

void cond(int v) {
    used[v] = true;
    color[v] = c;
    for (auto u : rev_g[v]) {
        if (!used[u]) {
            cond(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    used.resize(n);
    rev_g.resize(n);
    color.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].pb(y);
        rev_g[y].pb(x);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    fill(used.begin(), used.end(), 0);
    reverse(order.begin(), order.end());
    for (auto v : order) {
        if (!used[v]) {
            c++;
            cond(v);
        }
    }
    cout << c << endl;
    for (int i = 0; i < n; i++) {
        cout << color[i] << ' ';
    }
    return 0;
}
