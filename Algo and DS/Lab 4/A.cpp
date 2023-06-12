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

vector<vector<int> > dp;
vector<vector<int> > lr;
vector<int> v, open, close;

int solve(int l, int r) {
    if (dp[l][r] == -1) {
        if (l == r - 1) {
            dp[l][r] = 0;
            lr[l][r] = r;
        } else {
            dp[l][r] = INF;
            for (int i = l + 1; i < r; i++) {
                int t = v[l] * v[i] * v[r] + solve(l, i) + solve(i, r);
                if (t < dp[l][r]) {
                    dp[l][r] = t;
                    lr[l][r] = i;
                }
            }
        }
    }
    return dp[l][r];
}

void make_ans(int l, int r) {
    if (l >= r - 1) {
        return;
    }
    open[l]++;
    close[r]++;
    make_ans(l, lr[l][r]);
    make_ans(lr[l][r], r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ifstream cin("matrix.in");
    ofstream cout("matrix.out");
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (v.empty()) {
            v.pb(a);
        }
        v.pb(b);
    }
    dp.resize(n + 1, vector<int>(n + 1, -1));
    lr.resize(n + 1, vector<int>(n + 1, -1));
    open.resize(n + 1);
    close.resize(n + 1);
    solve(0, n);
    make_ans(0, n);
    for (int i = 0; i <= n; i++) {
        while (close[i]--) {
            cout << ")";
        }
        if (i == n) {
            return 0;
        }
        while (open[i]--) {
            cout << "(";
        }
        cout << "A";
    }
    return 0;
}
