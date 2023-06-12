#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 998244353;
const int mod1 = 999999937;
const int INF = 2e9;

vector<bool> erat(20000001, true);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    erat[0] = erat[1] = false;
    for (int i = 2; i < (int)erat.size(); i++) {
        if (erat[i]) {
            for (ll j = (ll)i * (ll)i; j < (ll)erat.size(); j += i) {
                erat[(int)j] = false;
            }
        }
    }

    while (n--) {
        int x;
        cin >> x;
        if (erat[x]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
