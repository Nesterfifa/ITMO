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
vector<pair<int, int> > points;
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

    int n;
    cin >> n;
    points.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.pb({(points[i].first - points[j].first)
                           * (points[i].first - points[j].first)
                           + (points[i].second - points[j].second)
                           * (points[i].second - points[j].second), {i, j}});
        }
    }
    p.resize(n);
    sort(edges.begin(), edges.end());
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    double ans = 0;
    for (size_t i = 0; i < edges.size(); i++) {
        int a = edges[i].second.first, b = edges[i].second.second;
        if (leader(a) != leader(b)) {
            ans += sqrt(edges[i].first);
            unite(a, b);
        }
    }
    cout << fixed << ans;
    return 0;
}
