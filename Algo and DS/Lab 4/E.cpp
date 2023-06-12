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

    ifstream cin("levenshtein.in");
    ofstream cout("levenshtein.out");

    string a, b;
    cin >> a >> b;
    int m = a.size(), n = b.size();
    vector<vector<int> > d(m + 1, vector<int> (n + 1));
    for (int i = 1; i <= n; i++) {
        d[0][i] = d[0][i - 1] + 1;
    }
    for (int i = 1; i <= m; i++) {
        d[i][0] = d[i - 1][0] + 1;
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] != b[j - 1]) {
                d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + 1);
            } else {
                d[i][j] = d[i - 1][j - 1];
            }
        }
    }
    cout << d[m][n];
    return 0;
}
