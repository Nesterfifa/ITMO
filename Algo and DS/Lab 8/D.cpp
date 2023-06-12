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

vector<vector<int> > g;
vector<int> used, f, topsort;

void dfs(int v) {
    used[v] = true;
    for (auto u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    topsort.pb(v);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, s;
    cin >> n >> m >> s;
    s--;

    g.resize(n);
    used.resize(n);
    f.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].pb(y);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    for (auto v : topsort) {
        int cnt = 0;
        unordered_set<int> mex_set;
        for (auto u : g[v]) {
            mex_set.insert(f[u]);
        }
        while (mex_set.count(cnt)) {
            cnt++;
        }
        f[v] = cnt;
    }
    if (f[s] == 0) {
        cout << "Second player wins";
    } else {
        cout << "First player wins";
    }
    return 0;
}
