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

vector<int> p, r, maxes, mins;

int leader(int v) {
    return (p[v] == v) ? v : p[v] = leader(p[v]);
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
    p[a] = b;
    r[b] += r[a];
    maxes[b] = max(maxes[b], maxes[a]);
    mins[b] = min(mins[b], mins[a]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        p.pb(i);
        maxes.pb(i);
        mins.pb(i);
        r.pb(1);
    }
    string req;
    while (cin >> req) {
        if (req == "get") {
            int v;
            cin >> v;
            v--; v = leader(v);
            cout << mins[v] + 1 << ' ' << maxes[v] + 1 << ' ' << r[v] << endl;
        } else {
            int a, b;
            cin >> a >> b;
            a--; b--;
            unite(a, b);
        }
    }
    return 0;
}
