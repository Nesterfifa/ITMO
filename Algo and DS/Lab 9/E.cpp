#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 6e18;

vector<pair<pair<int, int>, ll> > g;
vector<int> used(2000);
void dfs(int v) {
    used[v] = true;
    for (auto u : g) {
        if (u.first.first == v && !used[u.first.second]) {
            dfs(u.first.second);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, s;
    cin >> n >> m >> s;
    g.resize(m);
    s--;

    for (int i = 0; i < m; i++) {
        cin >> g[i].first.first >> g[i].first.second >> g[i].second;
        g[i].first.first--;
        g[i].first.second--;
    }

    vector<ll> d(n, INFLL);
    d[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (d[g[j].first.first] < INFLL) {
                d[g[j].first.second] = max(-3000000000000000000ll,
                    min(d[g[j].first.second], d[g[j].first.first] + g[j].second));
            }
        }
    }
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < m; j++) {
            if (d[g[j].first.first] < INFLL
                && d[g[j].first.first] + g[j].second < d[g[j].first.second]) {
                if (!used[g[j].first.second]) {
                    dfs(g[j].first.second);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (d[i] == INFLL) {
            cout << "*\n";
        } else if (used[i]) {
            cout << "-\n";
        } else {
            cout << d[i] << endl;
        }
    }
    return 0;
}
