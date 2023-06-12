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
const int mod1 = 999999937;
const int INF = 1e9;
const ll INFLL = 3e18;

vector<vector<ll> > matrix_mul(vector<vector<ll> > a, vector<vector<ll> > b) {
    vector<vector<ll> > res(a.size(), vector<ll>(b[0].size()));
    for (uint i = 0; i < a.size(); i++) {
        for (uint j = 0; j < b[0].size(); j++) {
            for (uint k = 0; k < a[0].size(); k++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= mod1;
            }
        }
    }
    return res;
}

vector<vector<ll> > binpow(vector<vector<ll> > &a, ll n) {
    if (n == 1) {
        return a;
    }
    ll m = n / 2;
    if (n % 2 == 1) {
        return matrix_mul(a, binpow(a, n - 1));
    } else {
        vector<vector<ll> > b = binpow(a, m);
        return matrix_mul(b, b);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ifstream cin("sequences.in");
    ofstream cout("sequences.out");

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) {
            return 0;
        }
        vector<vector<ll> > a(1, vector<ll>(5, 1)),
        b {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 0, 0}, {1, 1, 1, 1, 1}, {1, 1, 1, 0, 0}};
        a = matrix_mul(a, binpow(b, n));
        cout << a[0][0] << endl;
    }
}
