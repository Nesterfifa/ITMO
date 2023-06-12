#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define ins insert
#define x first
#define y second

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

    string s;
    for (int i = 0; i < 1000; i++) {
        s.pb('a');
    }
    int k;
    cin >> k;
    cout << s << endl;
    for (int i = 0; i < k - 1; i++) {
        string ans = s;
        ans[i] = 'b';
        ans[i + 1] = 'B';
        cout << ans << endl;
    }
    return 0;
}
