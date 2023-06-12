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
const int mod1 = 1e9 + 9;
const int INF = 1e9;
const ll INFLL = 3e18;

vector<int> dsuIndex(200005), dsu(200005), r(200005, 1);

int leaderIndex(int v) {
    return dsuIndex[v] == v ? v : dsuIndex[v] = leaderIndex(dsuIndex[v]);
}

int leader(int v) {
    return dsu[v] == v ? v : dsu[v] = leader(dsu[v]);
}

void unite(int a, int b) {
    a = leader(a);
    b = leader(b);
    if (a == b) {
        return;
    }
    if (r[a] > r[b]) {
        swap(a, b);
    }
    dsu[a] = b;
    r[b] += r[a];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n + 3; i++) {
        dsu[i] = i;
        dsuIndex[i] = i;
    }
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            l = leader(l);
            r = leader(r);
            unite(l, r);
        } else if (t == 2) {
            if (l == r) {
                continue;
            }
            while (true) {
                l = leaderIndex(l);
                if (l >= r) {
                    break;
                }
                unite(l, l + 1);
                dsuIndex[l] = l + 1;
            }
        } else {
            if (leader(r) == leader(l)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
