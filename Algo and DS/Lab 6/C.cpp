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

    ifstream cin("linkedmap.in");
    ofstream cout("linkedmap.out");

    string s, x, y;
    int m = 1e6;
    pair<int, int> last = {-1, -1};
    vector<vector<pair<string, string> > > hash_table(m);
    vector<vector<pair<int, int> > > link_prev(m), link_next(m);
    while (cin >> s >> x) {
        int h = hsh(x) % m;
        if (s == "put") {
            cin >> y;
            bool flag = 1;
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i].x == x) {
                    hash_table[h][i].y = y;
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                hash_table[h].pb({x, y});
                link_prev[h].pb(last);
                link_next[h].pb({-1, -1});
                if (last != make_pair(-1, -1)) {
                    link_next[last.x][last.y] = {h, hash_table[h].size() - 1};
                }
                last = {h, hash_table[h].size() - 1};
            }
        } else if (s == "delete") {
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i].x == x) {
                    hash_table[h][i].x = "";
                    if (link_prev[h][i] != make_pair(-1, -1)) {
                        link_next[link_prev[h][i].x][link_prev[h][i].y] = link_next[h][i];
                    }
                    if (link_next[h][i] != make_pair(-1, -1)) {
                        link_prev[link_next[h][i].x][link_next[h][i].y] = link_prev[h][i];
                    }
                    if (last == make_pair(h, (int)i)) {
                        last = link_prev[h][i];
                    }
                }
            }
        } else if (s ==  "get") {
            int flag = 1;
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i].x == x) {
                    cout << hash_table[h][i].y << endl;
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                cout << "none" << endl;
            }
        } else if (s == "next") {
            bool flag = 1;
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i].x == x && link_next[h][i] != make_pair(-1, -1)) {
                    flag = 0;
                    cout << hash_table[link_next[h][i].x][link_next[h][i].y].y << endl;
                    break;
                }
            }
            if (flag) {
                cout << "none" << endl;
            }
        } else {
            bool flag = 1;
            for (uint i = 0; i < hash_table[h].size(); i++) {
                if (hash_table[h][i].x == x && link_prev[h][i] != make_pair(-1, -1)) {
                    flag = 0;
                    cout << hash_table[link_prev[h][i].x][link_prev[h][i].y].y << endl;
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
