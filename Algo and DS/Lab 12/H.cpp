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

const ll p = 31;
vector<ll> pn(100001, 1);
vector<ll> pref_hash;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    int n = s.size();
    pref_hash.resize(n, s[0] - 'a' + 1);

    for (int i = 1; i < n; i++) {
        pn[i] = pn[i - 1] * p;
        pref_hash[i] = pref_hash[i - 1] + (ll)(s[i] - 'a' + 1) * pn[i];
    }
    int t;
    cin >> t;
    while (t--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        l1--; r1--; l2--; r2--;
        int len = r1 - l1 + 1;
        if (len != r2 - l2 + 1) {
            cout << "No\n";
            continue;
        }
        ll hash1 = pref_hash[l1 + len - 1] - (l1 ? pref_hash[l1 - 1] : 0);
        ll hash2 = pref_hash[l2 + len - 1] - (l2 ? pref_hash[l2 - 1] : 0);
        if ((l1 < l2 && hash1 * pn[l2 - l1] == hash2)
            || (l1 >= l2 && hash1 == hash2 * pn[l1 - l2])) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
