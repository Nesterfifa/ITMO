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
const int INF = 1e9;
const ll INFLL = 3e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n), fl(n + 1);
    vector<vector<int> > st(n + 1, vector<int>((uint)log2(n) + 1));
    cin >> a[0];
    int u, v;
    cin >> u >> v;
    for (int i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    for (int j = 0; j <= (int)log2(n); j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            if (j == 0) {
                st[i][j] = a[i];
            } else {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        fl[i] = (uint)log2(i);
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        int l = min(u, v), r = max(u, v);
        l--; r--;
        ans = min(st[l][fl[r - l + 1]], st[r - (1 << fl[r - l + 1]) + 1][fl[r - l + 1]]);
        if (i < m) {
            u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
            v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
        }
    }
    cout << u << ' ' << v << ' ' << ans;
    return 0;
}
