#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-15;
const int mod = 998244353;
const int mod1 = 999999937;
const int INF = 2e9;

ll mulmod(ll a, ll b, ll MOD)
{
    if (b == 0) return 0;
    if (b & 1) {
        return (a + mulmod(a, b - 1, MOD)) % MOD;
    } else {
        ll c = mulmod(a, b / 2, MOD);
        return (c + c) % MOD;
    }
}

ll powmod(ll a, ll b, ll MOD)
{
    if (b == 0) return 1;
    if (b & 1) {
        return mulmod(a, powmod(a, b - 1, MOD), MOD);
    } else {
        ll c = powmod(a, b / 2, MOD);
        return mulmod(c, c, MOD);
    }
}

ll gcd (ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = gcd (b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

vector<ll> fact(ll n) {
    vector<ll> res;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            res.pb(i);
            n /= i;
        }
    }
    if (n > 1) {
        res.pb(n);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n, e, c;
    cin >> n >> e >> c;
    vector<ll> f = fact(n);
    ll m = (f[0] - 1) * (f[1] - 1);
    ll d, t;
    gcd(e, m, d, t);
    d = (d % m + m) % m;
    cout << powmod(c, d, n);
    return 0;
}
