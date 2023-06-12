#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 1e9;
const ll INFLL = 6e18;

vector<vector<int> > g;
vector<int> used_l, used_r, mt, mt_used;

void dfs(int v, int p) {
    if (p == 1) {
        used_l[v] = true;
        for (auto u : g[v]) {
            if (mt[u] != v && !used_r[u]) {
                dfs(u, 2);
            }
        }
    } else {
        used_r[v] = true;
        if (mt[v] != -1 && !used_l[mt[v]]) {
            dfs(mt[v], 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    g.resize(n);
    used_l.resize(n);
    used_r.resize(m);
    mt.resize(m, -1);
    mt_used.resize(n);

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        while (k--) {
            int x;
            cin >> x;
            x--;
            g[i].pb(x);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        if (x == -1) { continue; }
        mt[x] = i;
        mt_used[i] = true;
        ans++;
    }
    for (int i = 0; i < n; i++) {
        if (!mt_used[i] && !used_l[i]) {
            dfs(i, 1);
        }
    }
    cout << ans << endl;
    cout << count(used_l.begin(), used_l.end(), false) << ' ';
    for (int i = 0; i < n; i++) {
        if (!used_l[i]) {
            cout << i + 1 << ' ';
        }
    }
    cout << endl;
    cout << count(used_r.begin(), used_r.end(), true) << ' ';
    for (int i = 0; i < m; i++) {
        if (used_r[i]) {
            cout << i + 1 << ' ';
        }
    }
    return 0;
}
