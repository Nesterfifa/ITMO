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

vector<set<int> > g;
set<pair<int, int> > bridges;
map<pair<int, int>, int> e_number;
vector<int> used, tin, fup;
int timer = 0;

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (auto u : g[v]) {
        if (u != p) {
            if (used[u]) {
                fup[v] = min(fup[v], tin[u]);
            } else {
                dfs(u, v);
                fup[v] = min(fup[v], fup[u]);
                if (fup[u] > tin[v]) {
                    bridges.insert({v, u});
                }
            }
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
    tin.resize(n);
    fup.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].insert(y);
        g[y].insert(x);
        e_number[{x, y}] = e_number[{y, x}] = i + 1;
    }
    dfs(0);
    vector<int> ans;
    for (auto b : bridges) {
        ans.pb(e_number[b]);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i << endl;
    }
    return 0;
}
