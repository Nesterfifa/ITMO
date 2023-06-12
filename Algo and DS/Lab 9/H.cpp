#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 1e9;
const ll INFLL = 6e18;

vector<pair<int, pair<int, int> > > edges;
vector<int> p;

int leader(int v) {
    return p[v] == v ? v : p[v] = leader(p[v]);
}

void unite(int a, int b) {
    a = leader(a);
    b = leader(b);
    if (rand() & 1) {
        swap(a, b);
    }
    p[a] = b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--; y--;
        edges.pb({w, {x, y}});
    }
    p.resize(n);
    sort(edges.begin(), edges.end());
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int a = edges[i].second.first, b = edges[i].second.second;
        if (leader(a) != leader(b)) {
            ans += edges[i].first;
            unite(a, b);
        }
    }
    cout << ans;
    return 0;
}
