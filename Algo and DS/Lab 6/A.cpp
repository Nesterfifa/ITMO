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

int hsh(int x) {
    return (int)(((ll)a * (ll)x + 100ll * (ll)p) % (ll)p);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ifstream cin("set.in");
    ofstream cout("set.out");

    string s;
    int x, m = 1e6;
    vector<vector<int> > hash_table(m);
    while (cin >> s >> x) {
        int h = hsh(x) % m;
        if (s == "insert") {
            bool flag = 1;
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i] == x) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                hash_table[h].pb(x);
            }
        } else if (s == "exists") {
            bool flag = 0;
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i] == x) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (s == "delete") {
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i] == x) {
                    hash_table[h][i] = 2000000000;
                    break;
                }
            }
        }
    }
    return 0;
}
