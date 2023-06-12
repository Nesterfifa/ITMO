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
set<int> cutverts;
map<pair<int, int>, int> e_numbers;
vector<int> used, tin, fup, color;
int timer = 0, col = 0;

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int c = 0;
    for (auto u : g[v]) {
        if (u != p) {
            if (used[u]) {
                fup[v] = min(fup[v], tin[u]);
            } else {
                dfs(u, v);
                fup[v] = min(fup[v], fup[u]);
                if (fup[u] >= tin[v] && p != -1) {
                    cutverts.insert(v);
                }
                c++;
            }
        }
    }
    if (p == -1 && c > 1) {
        cutverts.insert(v);
    }
}

void paint(int v, int c, int p) {
    used[v] = true;
    for (auto u : g[v]) {
        if (u != p) {
            if (!used[u]) {
                if (fup[u] >= tin[v]) {
                    color[e_numbers[{v, u}]] = ++col;
                    paint(u, col, v);
                } else {
                    color[e_numbers[{v, u}]] = c;
                    paint(u, c, v);
                }
            } else if (tin[u] < tin[v]) {
                color[e_numbers[{v, u}]] = c;
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
    color.resize(m);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].insert(y);
        g[y].insert(x);
        e_numbers[{x, y}] = e_numbers[{y, x}] = i;
    }
    dfs(0);
    fill(used.begin(), used.end(), 0);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            paint(i, col, -1);
        }
    }
    cout << col << endl;
    for (auto e : color) {
        cout << e << ' ';
    }
    return 0;
}
