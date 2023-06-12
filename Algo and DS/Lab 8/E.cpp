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

vector<vector<int> > g;
vector<int> color, cycle;
int begin_cycle = -1;

void dfs(int v) {
    color[v] = 1;
    for (auto u : g[v]) {
        if (begin_cycle != -1) {
            break;
        }
        if (color[u] == 1) {
            begin_cycle = u;
        } else if (color[u] == 0) {
            dfs(u);
        }
    }
    if (begin_cycle != -1) {
        cycle.pb(v);
    }
    if (begin_cycle == v) {
        reverse(cycle.begin(), cycle.end());
        cout << "YES\n";
        for (auto i : cycle) {
            cout << i + 1 << ' ';
        }
        exit(0);
    }
    color[v] = 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    g.resize(n);
    color.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].pb(y);
    }
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i);
        }
    }
    cout << "NO";
    return 0;
}
