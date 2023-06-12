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

int a = 47, b = 31, p = 1e9 + 7, q = 1e9 + 9;

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

int hsh1(string s) {
    ll res = 0;
    for (uint i = 0; i < s.size(); i++) {
        res = (res + (ll)s[i] * (ll)binpow(a, i)) % p;
    }
    return (int)res;
}

int hsh2(string s) {
    ll res = 0;
    for (uint i = 0; i < s.size(); i++) {
        res = (res + (ll)s[i] * (ll)binpow(b, i)) % p;
    }
    return (int)res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ifstream cin("multimap.in");
    ofstream cout("multimap.out");

    string s, x, y;
    int m = 100;
    vector<vector<pair<string, pair<vector<vector<string> >, vector<int> > > > > hash_table(m);
    while (cin >> s >> x) {
        int h1 = hsh1(x) % m;
        if (s == "put") {
            cin >> y;
            int h2 = hsh2(y) % m;
            bool flag = 1;
            for (uint i = 0; i < hash_table[h1].size(); i++) {
                if (hash_table[h1][i].x == x) {
                    flag = 0;
                    bool inner_flag = 1;
                    for (uint j = 0; j < hash_table[h1][i].y.x[h2].size(); j++) {
                        if (hash_table[h1][i].y.x[h2][j] == y) {
                            inner_flag = 0;
                            break;
                        }
                    }
                    if (inner_flag) {
                        bool deep_flag1 = 1, deep_flag2 = 1;
                        for (uint j = 0; j < hash_table[h1][i].y.x[h2].size(); j++) {
                            if (hash_table[h1][i].y.x[h2][j] == "") {
                                hash_table[h1][i].y.x[h2][j] = y;
                                deep_flag1 = 0;
                                break;
                            }
                        }
                        if (deep_flag1) {
                            hash_table[h1][i].y.x[h2].pb(y);
                        }
                        for (uint j = 0; j < hash_table[h1][i].y.y.size(); j++) {
                            if (hash_table[h1][i].y.y[j] == h2) {
                                deep_flag2 = 0;
                                break;
                            }
                        }
                        if (deep_flag2) {
                            for (uint j = 0; j < hash_table[h1][i].y.y.size(); j++) {
                                if (hash_table[h1][i].y.y[j] == -1) {
                                    deep_flag2 = 0;
                                    hash_table[h1][i].y.y[j] = h2;
                                    break;
                                }
                            }
                            if (deep_flag2) {
                                hash_table[h1][i].y.y.pb(h2);
                            }
                        }
                    }
                    break;
                }
            }
            if (flag) {
                for (uint i = 0; i < hash_table[h1].size(); i++) {
                    if (hash_table[h1][i].x == "") {
                        flag = 0;
                        hash_table[h1][i].x = x;
                        hash_table[h1][i].y.y.pb(h2);
                        hash_table[h1][i].y.x[h2].pb(y);
                        break;
                    }
                }
                if (flag) {
                    hash_table[h1].pb({});
                    hash_table[h1].back().x = x;
                    hash_table[h1].back().y.y.pb(h2);
                    hash_table[h1].back().y.x.resize(m);
                    hash_table[h1].back().y.x[h2].pb(y);
                }
            }
        } else if (s == "delete") {
            cin >> y;
            int h2 = hsh2(y) % m;
            for (uint i = 0; i < hash_table[h1].size(); i++) {
                if (hash_table[h1][i].x == x) {
                    bool cnt = 0;
                    for (uint j = 0; j < hash_table[h1][i].y.x[h2].size(); j++) {
                        if (hash_table[h1][i].y.x[h2][j] == y) {
                            hash_table[h1][i].y.x[h2][j] = "";
                        }
                        if (hash_table[h1][i].y.x[h2][j] != "") {
                            cnt |= 1;
                        }
                    }
                    if (!cnt) {
                        for (uint j = 0; j < hash_table[h1][i].y.y.size(); j++) {
                            if (hash_table[h1][i].y.y[j] == h2) {
                                hash_table[h1][i].y.y[j] = -1;
                                break;
                            }
                        }
                    }
                }
            }
        } else if (s == "get") {
            vector<string> ans;
            for (uint i = 0; i < hash_table[h1].size(); i++) {
                if (hash_table[h1][i].x == x) {
                    for (uint j = 0; j < hash_table[h1][i].y.y.size(); j++) {
                        if (hash_table[h1][i].y.y[j] != -1) {
                            int h2 = hash_table[h1][i].y.y[j];
                            for (uint k = 0; k < hash_table[h1][i].y.x[h2].size(); k++) {
                                if (hash_table[h1][i].y.x[h2][k] != "") {
                                    ans.pb(hash_table[h1][i].y.x[h2][k]);
                                }
                            }
                        }
                    }
                    break;
                }
            }
            cout << ans.size() << " ";
            if (ans.empty()) {
                cout << "\n";
            }
            for (uint i = 0; i < ans.size(); i++) {
                cout << ans[i];
                if (i == ans.size() - 1) {
                    cout << "\n";
                } else {
                    cout << " ";
                }
            }
        } else {
            for (uint i = 0; i < hash_table[h1].size(); i++) {
                if (hash_table[h1][i].x == x) {
                    hash_table[h1][i].x = "";
                    hash_table[h1][i].y.y.clear();
                    vector<string> t;
                    fill(hash_table[h1][i].y.x.begin(), hash_table[h1][i].y.x.end(), t);
                }
            }
        }
    }
    return 0;
}
