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

    ifstream cin("lis.in");
    ofstream cout("lis.out");
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    vector<int> dp(n + 1, INF), idx(n + 1), p(n);
    dp[0] = -INF; idx[0] = -1;
    int l = 0;
    for (int i = 0; i < n; i++) {
        int j = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        if (dp[j - 1] < a[i] && a[i] < dp[j]) {
            dp[j] = a[i];
            idx[j] = i;
            p[i] = idx[j - 1];
            l = max(l, j);
        }
    }
    vector<int> ans;
    int k = idx[l];
    while (k > -1) {
        ans.pb(a[k]);
        k = p[k];
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i << ' ';
    }
    return 0;
}
