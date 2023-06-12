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

inline int fastrand() {
  g_seed = (214013*g_seed+2531011);
  return (g_seed>>16)&0x7FFF;
}

int main() {
    int n, m;
    vector<pair<int, int> > edges;
    vector<int> colors;

    cin >> n >> m;
    colors.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        edges.pb({min(x, y), max(x, y)});
    }
    for (int i = 0; i < n; i++) {
        colors[i] = fastrand() % 3;
    }
    while (true) {
        bool flag = true;
        for (int i = 0; i < m; i++) {
            if (colors[edges[i].first] == colors[edges[i].second]) {
                flag = false;
                int fs = fastrand() % 2;
                if (fs) {
                    colors[edges[i].first] = (colors[edges[i].first] + 1 + fastrand() % 2) % 3;
                } else {
                    colors[edges[i].second] = (colors[edges[i].second] + 1 + fastrand() % 2) % 3;
                }
                break;
            }
        }
        if (flag) {
            for (auto u : colors) {
                cout << u + 1 << " ";
            }
            return 0;
        }
    }
    return 0;
}
