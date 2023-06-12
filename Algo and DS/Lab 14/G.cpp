#include <iostream>
#include <unordered_map>
#include <cmath>

typedef long long ll;

ll mulmod(ll a, ll b, ll MOD)
{
    ll res = 0;
	while (b) {
		if (b % 5000000 != 0) {
			res = (res + a * (b % 5000000) % MOD) % MOD;
			b -= b % 5000000;
		} else {
            a *= 5000000;
            a %= MOD;
            b /= 5000000;
		}
	}
	return res;
}

ll powmod(ll a, ll b, ll MOD)
{
    ll res = 1;
	while (b) {
		if (b & 1) {
			res = mulmod(res, a, MOD);
		}
		a = mulmod(a, a, MOD);
		b >>= 1;
	}
	return res;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    ll a, b, n;
    std::cin >> a >> b >> n;
    std::unordered_map<ll, ll> pows;
    // а так мб и в секунду влезем
    ll s = (ll)sqrt((double)n);
    ll pow = 1;
    const ll as = powmod(a, s, n);
    for (ll i = 0; i <= (n - 2) / s; i++) {
        if (i == 0) {
            pows[pow] = i;
        } else {
            pow = mulmod(pow, as, n);
            pows[pow] = i;
        }
    }
    ll ans = -1;
    pow = 1;
    for (ll i = 0; i < s; i++) {
        if (i > 0) {
            pow = mulmod(pow, a, n);
        }
        ll x = mulmod(b, pow, n);
        if (pows.count(x)) {
            ll v = mulmod(pows[x], s, n) - i;
            if (powmod(a, v, n) == b) {
                ans = mulmod(pows[x], s, n) - i;
                break;
            }
        }
    }
    std::cout << ans;
    return 0;
}
