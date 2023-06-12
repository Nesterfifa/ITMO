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

vector<multiset<int> > g;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, start = 0;
    cin >> n >> m;
    if (n == 1) {
        cout << 1 << endl;
        for (int i = 0; i <= m; i++) {
            cout << 1 << ' ';
        }
        return 0;
    }

    g.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x - 1].insert(y - 1);
        g[y - 1].insert(x - 1);
    }
    vector<int> odd;
    set<pair<int, int> > added;
    for (int i = 0; i < n; i++) {
        if (g[i].size() % 2 == 1) {
            odd.pb(i);
        }
    }
    for (size_t i = 0; i < odd.size(); i += 2) {
        g[odd[i]].insert(odd[i + 1]);
        g[odd[i + 1]].insert(odd[i]);
        added.insert({odd[i], odd[i + 1]});
        added.insert({odd[i + 1], odd[i]});
    }

    stack<int> st;
    vector<int> ans;
    st.push(start);
    while (!st.empty()) {
        int v = st.top();
        if (!g[v].empty()) {
            st.push(*g[v].begin());
            g[*g[v].begin()].erase(g[*g[v].begin()].find(v));
            g[v].erase(g[v].begin());
        } else {
            st.pop();
            ans.pb(v);
        }
    }
    cout << max(odd.size() / 2, static_cast<size_t>(1)) << endl;
    for (size_t i = 0; i + 1 < ans.size(); i++) {
        if (added.count({ans[i], ans[i + 1]})) {
            added.erase({ans[i], ans[i + 1]});
            added.erase({ans[i + 1], ans[i]});
            for (size_t j = 1; j <= i; j++) {
                ans.pb(ans[j]);
            }
            ans.erase(ans.begin(), ans.begin() + i + 1);
            break;
        }
    }
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << ' ';
        if (i + 1 < ans.size() && added.count({ans[i], ans[i + 1]})) {
            cout << endl;
            added.erase({ans[i], ans[i + 1]});
            added.erase({ans[i + 1], ans[i]});
        }
    }
    return 0;
}
