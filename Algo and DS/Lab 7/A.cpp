#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define x first
#define y second

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 1e9;
const ll INFLL = 3e18;

uint cur = 0, a, b;
uint next_rand() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m, q;
    cin >> m >> q >> a >> b;
    vector<uint> v(1 << 24);
    uint n = v.size();
    while (m--) {
        uint add = next_rand();
        uint l = next_rand();
        uint r = next_rand();
        if (l > r) {
            swap(l, r);
        }
        v[l] += add;
        if (r < n - 1) {
            v[r + 1] -= add;
        }
    }
    vector<uint> pref(1 << 24);
    for (uint i = 1; i < n; i++) {
        v[i] += v[i - 1];
    }
    pref[0] = v[0];
    for (uint i = 1; i < n; i++) {
        pref[i] = v[i] + pref[i - 1];
    }
    uint ans = 0;
    while (q--) {
        uint l = next_rand();
        uint r = next_rand();
        if (l > r) {
            swap(l, r);
        }
        ans += pref[r];
        if (l > 0) {
            ans -= pref[l - 1];
        }
    }
    cout << ans;
    return 0;
}
