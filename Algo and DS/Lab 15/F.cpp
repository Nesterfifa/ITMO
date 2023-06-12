#include <iostream>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 998244353;
const int mod1 = 999999937;
const int INF = 2e9;

int g_seed = 134135113;

int n, m;
vector<pair<int, int> > edges;
vector<int> colors;
vector<vector<pair<int, int> > > g;
vector<pair<int, int> > ededges;
vector<vector<int> > edg;

inline int fastrand() {
  g_seed = (214013*g_seed+2531011);
  return (g_seed>>16)&0x7FFF;
}

bool dfs(int v, int col) {
    colors[v] = col;
    bool ans = true;
    for (auto u : edg[v]) {
        if (colors[v] == colors[u]) {
            ans = false;
            break;
        }
        if (colors[u] == -1) {
            ans &= dfs(u, 1 - col);
        }
    }
    return ans;
}

int main() {
    cin >> n >> m;
    colors.resize(m, -1);
    g.resize(n);
    edg.resize(m);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        edges.pb({min(x, y), max(x, y)});
        g[x].pb({y, i});
        g[y].pb({x, i});
    }
    for (int i = 0; i < n; i++) {
        for (auto u : g[i]) {
            for (auto v : g[i]) {
                if (u != v) {
                    ededges.pb({u.second, v.second});
                    edg[u.second].pb(v.second);
                    edg[v.second].pb(u.second);
                }
            }
        }
    }
    bool ot = true;
    for (int i = 0; i < m; i++) {
        if (colors[i] == -1) {
            ot &= dfs(i, 0);
        }
    }
    if (ot) {
        cout << "YES\n";
        for (auto u : colors) {
            cout << u + 1 << " ";
        }
        return 0;
    }

    for (int i = 0; i < m; i++) {
        colors[i] = fastrand() % 3;
    }
    while (double(clock()) / CLOCKS_PER_SEC < 0.91) {
        bool flag = true;
        for (int i = 0; i < (int)ededges.size(); i++) {
            if (colors[ededges[i].first] == colors[ededges[i].second]) {
                flag = false;
                int fs = fastrand() % 2;
                if (fs) {
                    colors[ededges[i].first] = (colors[ededges[i].first] + 1 + fastrand() % 2) % 3;
                } else {
                    colors[ededges[i].second] = (colors[ededges[i].second] + 1 + fastrand() % 2) % 3;
                }
                break;
            }
        }
        if (flag) {
            cout << "YES\n";
            for (auto u : colors) {
                cout << u + 1 << " ";
            }
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
