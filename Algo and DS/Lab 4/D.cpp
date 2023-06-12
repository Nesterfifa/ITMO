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

    ifstream cin("knapsack.in");
    ofstream cout("knapsack.out");
    int n, m;
    cin >> n >> m;
    vector<int> c(n), w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<vector<int> > dp(n + 1, vector<int> (m + 1, -1)), p(n + 1, vector<int> (m + 1, -1));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == -1) {
                continue;
            }
            if (j + w[i] <= m && dp[i + 1][j + w[i]] < dp[i][j] + c[i]) {
                dp[i + 1][j + w[i]] = dp[i][j] + c[i];
                p[i + 1][j + w[i]] = i;
            }
            if (dp[i + 1][j] < dp[i][j]) {
                dp[i + 1][j] = dp[i][j];
                p[i + 1][j] = -1;
            }
        }
    }
    int answ = -1, ansc = -1;
    for (int i = 0; i <= m; i++) {
        if (dp[n][i] > ansc) {
            ansc = dp[n][i];
            answ = i;
        }
    }
    vector<int> ans;
    int k = n;
    while (k > 0) {
        if (p[k][answ] != -1) {
            ans.pb(p[k][answ] + 1);
            answ -= w[p[k][answ]];
        }
        k--;
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i << " ";
    }
    return 0;
}
