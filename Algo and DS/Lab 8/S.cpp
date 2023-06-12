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

int t = 1;
vector<vector<int> > g;
vector<int> a;
set<pair<int, int> > edges;

void solve(int v, int p) {
    while (t < (int)a.size()) {
        if (p != a[t]) {
            t++;
            solve(a[t - 1], v);
        } else {
            g[p].pb(v);
            edges.insert({p, v});
            for (int i = 0; i < (int)g[v].size(); i++) {
                if (g[v][i] > v) {
                    edges.insert({p, g[v][i]});
                }
                g[p].pb(g[v][i]);
            }
            t++;
            break;
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
    a.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        a[i]--;
    }
    solve(a[0], -1);
    cout << edges.size() << endl;
    for (auto u : edges) {
        cout << u.first + 1 << " " << u.second + 1 << endl;
    }
    return 0;
}
