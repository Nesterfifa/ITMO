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

vector<int> g[100000];
vector<int> topsort, color(100000);
bool able = true;

void dfs(int v, int p = -1) {
    color[v] = 1;
    for (auto u : g[v]) {
        if (color[u] == 0) {
            dfs(u, v);
        } else if (color[u] == 1 && u != p) {
            able = false;
        }
    }
    color[v] = 2;
    topsort.pb(v + 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
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
    if (!able) {
        cout << -1;
    } else {
        reverse(topsort.begin(), topsort.end());
        for (auto v : topsort) {
            cout << v << ' ';
        }
    }
    return 0;
}
