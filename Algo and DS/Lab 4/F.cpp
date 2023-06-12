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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string p, s;
    getline(cin, p);
    getline(cin, s);
    if (s.empty()) {
        for (auto i : p) {
            if (i != '*') {
                cout << "NO";
                return 0;
            }
        }
        cout << "YES";
        return 0;
    }
    if (p.empty()) {
        if (s.empty()) {
            cout << "YES";
        } else {
            cout << "NO";
        }
        return 0;
    }
    p = "#" + p;
    s = "#" + s;
    int m = s.size(), n = p.size();
    vector<vector<bool> > dp(n, vector<bool> (m));
    dp[0][0] = true;
    for (int i = 1; i < n && p[i] == '*'; i++) {
        dp[i][0] = true;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (p[i] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1] || dp[i - 1][j - 1];
            } else if (p[i] == '?') {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = dp[i - 1][j - 1] && (s[j] == p[i]);
            }
        }
    }
    if (dp[n - 1][m - 1]) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
