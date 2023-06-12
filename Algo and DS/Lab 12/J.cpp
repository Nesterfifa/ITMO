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

    string c;
    cin >> c;
    string s = "";
    vector<int> pref;
    for (int i = 0; i < (int)c.size(); i++) {
        s.pb(c[i]);
        reverse(s.begin(), s.end());
        int n = (int)s.size();
        vector<int> z(n);
        int l = 0, r = 0;
        for (int i = 1; i < n; i++) {
            if (i <= r) {
                z[i] = min(z[i - l], r - i + 1);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        pref.pb(i == 0 ? 0 : pref.back());
        pref[pref.size() - 1] += n - *max_element(z.begin(), z.end());
        reverse(s.begin(), s.end());
    }
    for (auto u : pref) {
        cout << u << endl;
    }
    return 0;
}
