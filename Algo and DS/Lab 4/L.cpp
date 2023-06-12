#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define ins insert

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 1e9;
const ll INFLL = 3e18;

vector<vector<pair<int, ll> > > g;
vector<ll> a, b;

void dfs(int v, int p = -1) {
    for (auto i : g[v]) {
        if (i.first != p) {
            dfs(i.first, v);
            a[v] = max(a[v], b[i.first] + i.second - max(b[i.first], a[i.first]));
            b[v] += max(b[i.first], a[i.first]);
        }
    }
    a[v] += b[v];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ifstream cin("matching.in");
    ofstream cout("matching.out");

    int n;
    cin >> n;
    g.resize(n);
    a.resize(n);
    b.resize(n);
    for (int i = 0; i + 1 < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--; y--;
        g[x].pb({y, w});
        g[y].pb({x, w});
    }
    dfs(0);
    cout << max(a[0], b[0]);
    return 0;
}
