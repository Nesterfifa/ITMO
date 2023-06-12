#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 998244353;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 6e18;

int n, m;
string s;
vector<pair<int, int> > edges;
vector<char> colors;

const char num_to_col[3] {'R', 'G', 'B'};
map<char, char> nex;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    nex['R'] = 'G';
    nex['G'] = 'B';
    nex['B'] = 'R';
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        edges.pb({x, y});
    }
    srand(time(0));
    for (int i = 0; i < n; i++) {
        colors.pb(nex[s[i]]);
    }
    int flag;
    for (int timer = 0; timer < 1e6;) {
        flag = 1;
        for (int i = 0; i < m; i++) {
            if (colors[edges[i].first] == colors[edges[i].second]) {
                flag = 0;
                int fs = rand() % 2;
                while (true) {
                    timer++;
                    if (timer >= 1e6) {
                        cout << "Impossible";
                        return 0;
                    }
                    colors[fs ? edges[i].first : edges[i].second] = num_to_col[rand() % 3];
                    if (colors[fs ? edges[i].first : edges[i].second] != s[fs ? edges[i].first : edges[i].second]) {
                        break;
                    }
                }
                break;
            }
        }
        if (flag) {
            break;
        }
    }
    if (flag) {
        for (auto u : colors) {
            cout << u;
        }
    } else {
        cout << "Impossible";
    }
    return 0;
}
