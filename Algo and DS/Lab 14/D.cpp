#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-15;
const int mod = 998244353;
const int mod1 = 999999937;
const int INF = 2e9;

long long mulmod(long long a, long long b, long long MOD)
{
    if (b == 0) return 0;
    if (b & 1) {
        return (a + mulmod(a, b - 1, MOD)) % MOD;
    } else {
        ll c = mulmod(a, b / 2, MOD);
        return (c + c) % MOD;
    }
}

long long powmod(long long a, long long b, long long MOD)
{
    if (b == 0) return 1;
    if (b & 1) {
        return mulmod(a, powmod(a, b - 1, MOD), MOD);
    } else {
        ll c = powmod(a, b / 2, MOD);
        return mulmod(c, c, MOD);
    }
}

bool miller_rabin(ll n) {
    ll s = n - 1;
    ll k = 0;
    while (s % 2 == 0) {
        s /= 2;
        k++;
    }
    for (int i = 0; i < 5; i++) {
        ll y = powmod(2 + rand() % (n - 2), s, n);
        if (y == 1 || y == n - 1) continue;
        for (int j = 0; j < k; j++) {
            y = mulmod(y, y, n);
            if (y == 1) {
                return false;
            }
            if (y == n - 1) {
                break;
            }
        }
        if (y != n - 1) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    while (n--) {
        ll x;
        cin >> x;
        if (x == 1) {
            cout << "NO\n";
            continue;
        }
        if (x == 2 || miller_rabin(x)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
