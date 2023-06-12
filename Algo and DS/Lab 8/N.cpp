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

int n;
int a[1000][1000], cur_a[1000][1000];
vector<int> used(1000);

void dfs(int v, int dir) {
    used[v] = true;
    for (int i = 0; i < n; i++) {
        if (((!dir && cur_a[v][i] > 0) || (dir && cur_a[i][v] > 0)) && !used[i]) {
            dfs(i, dir);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    int l = 0, r = 1e9 + 1;
    while (r > l) {
        int m = (r + l) / 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cur_a[i][j] = a[i][j] <= m;
            }
        }
        int flag = true;
        fill(used.begin(), used.end(), 0);
        dfs(0, 0);
        if (count(used.begin(), used.end(), 1) < n) {
            flag = false;
        }
        fill(used.begin(), used.end(), 0);
        dfs(0, 1);
        if (count(used.begin(), used.end(), 1) < n) {
            flag = false;
        }
        if (flag) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l;
    return 0;
}
