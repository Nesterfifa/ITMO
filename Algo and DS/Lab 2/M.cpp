#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back
#define ins insert

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 1e9 + 9;
const int INF = 1e9;
const ll INFLL = 3e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int> > > net(k);
    for (int i = 0; i < k; i++) {
        int q;
        cin >> q;
        while (q--) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            if (x > y) {
                swap(x, y);
            }
            net[i].pb({x, y});
        }
    }
    for (int p = 0; p < (1 << n); p++) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = (bool)(p & (1 << i));
        }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < (int)net[i].size(); j++) {
                if (a[net[i][j].first]) {
                    swap(a[net[i][j].first], a[net[i][j].second]);
                }
            }
        }
        for (int i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
    return 0;
}
