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
int w[1000][1000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, start = 0;
    cin >> n;

    g.resize(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        if (m % 2 == 1) {
            start = i;
        }
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            g[i].insert(x - 1);
            w[i][x - 1]++;
        }
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
    cout << ans.size() - 1 << endl;
    for (auto i : ans) {
        cout << i + 1 << ' ';
    }
    return 0;
}
