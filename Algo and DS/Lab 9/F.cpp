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

struct edge {
    int x, y, w;

    edge(int x_, int y_, int w_) : x(x_), y(y_), w(w_) {}
};

vector<edge> g;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (w != 1000000000) {
                g.pb(edge(i, j, w));
            }
        }
    }
    for (int i = 0; i < min(n, 100); i++) {
        vector<int> d(n, INF);
        vector<int> p(n);
        d[i] = 0;
        for (int j = 0; j < n - 1; j++) {
            for (auto e : g) {
                if (d[e.y] > d[e.x] + e.w) {
                    d[e.y] = d[e.x] + e.w;
                    p[e.y] = e.x;
                }
            }
        }
        for (auto e : g) {
            if (d[e.y] > d[e.x] + e.w) {
                vector<int> ans;
                int u = e.x, v = e.y;
                d[e.y] = d[e.x] + e.w;
                p[e.y] = e.x;
                for (int j = 0; j < n - 1; j++) {
                    v = p[v];
                }
                u = v;
                while (u != p[v]) {
                    ans.pb(v);
                    v = p[v];
                }
                ans.pb(v);
                ans.pb(u);
                reverse(ans.begin(), ans.end());
                cout << "YES\n" << ans.size() << endl;
                for (auto v : ans) {
                    cout << v + 1 << ' ';
                }
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}
