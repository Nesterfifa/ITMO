#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define ins insert

const double pi = 3.14159265359;
const double eps = 1e-9;
const uint mod = 1e9 + 7;
const uint mod1 = 1e9 + 9;
const uint INF = 1e9;
const ll INFLL = 3e18;

uint cur = 0, a, b, n;
ll k, ans = 0;

uint nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

uint nextRand32() {
    uint aa = nextRand24(), bb = nextRand24();
    return (aa << 8) ^ bb;
}

void merge(ll a[], uint l, uint r) {
    vector<ll> b, c;
    for (uint i = l; i <= (l + r) / 2; i++) {
        b.pb(a[i]);
    }
    for (uint i = (r + l) / 2 + 1; i <= r; i++) {
        c.pb(a[i]);
    }
    uint L = 0, R = 0;
    while (L < b.size() || R < c.size()) {
        if (L == b.size()) {
            a[l++] = c[R++];
        } else if (R == c.size()) {
            a[l++] = b[L++];
        } else if (b[L] < c[R]) {
            a[l++] = b[L++];
        } else {
            a[l++] = c[R++];
        }
    }
}

int v[3000000];
ll pref[3000001];

void mergesort(ll a[], uint l, uint r) {
    if (l == r) {
        return;
    }
    uint m = (l + r) / 2;
    mergesort(a, l, m);
    mergesort(a, m + 1, r);
    uint i = l, j = m + 1;
    for (i = l; i <= m; i++) {
        while (j <= r && a[j] - a[i] < k) {
            j++;
        }
        ans += r - j + 1;
    }
    merge(a, l, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> a >> b;
    for (uint i = 0; i < n; i++) {
        v[i] = (int)nextRand32();
        pref[i + 1] = v[i] + pref[i];
    }
    mergesort(pref, 0, n);
    cout << ans;
    return 0;
}
