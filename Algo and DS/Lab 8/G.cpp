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
vector<int> used, color;
int c = 0;

void dfs(int v) {
    used[v] = true;
    color[v] = c;
    for (auto u : g[v]) {
        if (!used[u]) {
            dfs(u);
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
    color.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].insert(y);
        g[y].insert(x);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            c++;
            dfs(i);
        }
    }
    cout << c << endl;
    for (int i = 0; i < n; i++) {
        cout << color[i] << ' ';
    }
    return 0;
}
