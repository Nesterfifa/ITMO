#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 6e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int> > a(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> v(n + 1), u(n + 1), p(n + 1), w(n + 1);
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j1 = 0;
        vector<int> minv(n + 1, INF), used(n + 1);
        while (p[j1] != 0) {
            used[j1] = true;
            int delta = INF, j2 = 0;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    int cur = a[p[j1]][j] - u[p[j1]] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        w[j] = j1;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j2 = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j1 = j2;
        }
        while (j1) {
            int j2 = w[j1];
            p[j1] = p[j2];
            j1 = j2;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += a[p[i]][i];
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++) {
        cout << p[i] << ' ' << i << endl;
    }
    return 0;
}
