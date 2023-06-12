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

vector<int> p, r;

int leader(int v) {
    return p[v] == v ? v : p[v] = leader(p[v]);
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
    r[b] += r[a];
    p[a] = b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<string, pair<int, int> > > reqs(k);
    vector<pair<int, int> > e(m);
    set<pair<int, int> > cutted;
    vector<string> ans;
    p.resize(n);
    r.resize(n, 1);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> e[i].first >> e[i].second;
        e[i].first--, e[i].second--;
    }
    while (k--) {
        string s;
        int a, b;
        cin >> s >> a >> b;
        a--; b--;
        reqs[k] = make_pair(s, make_pair(a, b));
        if (s == "cut") {
            cutted.insert({a, b});
            cutted.insert({b, a});
        }
    }
    for (auto i : e) {
        if (!cutted.count({i.first, i.second})) {
            unite(i.first, i.second);
        }
    }
    for (auto q : reqs) {
        if (q.first == "cut") {
            unite(q.second.first, q.second.second);
        } else {
            if (leader(q.second.first) == leader(q.second.second)) {
                ans.pb("YES\n");
            } else {
                ans.pb("NO\n");
            }
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << i;
    }
    return 0;
}
