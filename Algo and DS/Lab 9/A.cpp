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
vector<int> used, d;

void bfs(int start) {
    d[start] = 0;
    used[start] = true;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (!used[u]) {
                used[u] = true;
                d[u] = d[v] + 1;
                q.push(u);
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
    d.resize(n);
    used.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].pb(y);
        g[y].pb(x);
    }
    bfs(0);
    for (auto u : d) {
        cout << u << " ";
    }
    return 0;
}
