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
const int mod1 = 1e9 + 9;
const int INF = 1e9;
const ll INFLL = 3e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ifstream cin("salesman.in");
    ofstream cout("salesman.out");
    int n, m;
    cin >> n >> m;
    n++;
    vector<vector<ll> > w(n, vector<ll> (n, -1));
    for (int i = 1; i < n; i++) {
        w[0][i] = w[i][0] = 0;
    }
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        w[x][y] = w[y][x] = c;
    }
    vector<vector<ll> > dp(n, vector<ll> (1 << n, INFLL));
    dp[0][0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (w[i][j] != -1 && (bool)(mask & (1 << j))
                    && dp[i][mask] > dp[j][mask - (1 << j)] + w[i][j]) {
                    dp[i][mask] = dp[j][mask - (1 << j)] + w[i][j];
                }
            }
        }
    }
    if (dp[0][(1 << n) - 1] != INFLL) {
        cout << dp[0][(1 << n) - 1];
    } else {
        cout << -1;
    }
    return 0;
}
