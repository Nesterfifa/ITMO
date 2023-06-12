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

int a = rand(), p = 1e9 + 9;

int binpow(int a, int n) {
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 1) {
        return (int)((ll)a * (ll)binpow(a, n - 1) % p);
    }
    int b = binpow(a, n / 2) % p;
    return (int)((ll)b *(ll)b % p);
}

int hsh(string s) {
    ll res = 0;
    for (uint i = 0; i < s.size(); i++) {
        res = (res + (ll)s[i] * (ll)binpow(a, i)) % p;
    }
    return (int)res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ifstream cin("map.in");
    ofstream cout("map.out");

    string s, x, y;
    int m = 1e6;
    vector<vector<pair<string, string> > > hash_table(m);
    while (cin >> s >> x) {
        int h = hsh(x) % m;
        if (s == "put") {
            cin >> y;
            bool flag = 1;
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i].first == x) {
                    hash_table[h][i].second = y;
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                hash_table[h].pb({x, y});
            }
        } else if (s == "delete") {
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i].first == x) {
                    hash_table[h][i].first = "";
                }
            }
        } else {
            int flag = 1;
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i].first == x) {
                    cout << hash_table[h][i].second << endl;
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                cout << "none" << endl;
            }
        }
    }
    return 0;
}
