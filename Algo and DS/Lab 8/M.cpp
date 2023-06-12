#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define x first
#define y second

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 3e18;

vector<string> nums;
vector<vector<int> > g(26);
vector<int> color(26), topsort, comp(26);
set<int> cant_be_zero;
int col = 0;

void dfs(int v) {
    color[v] = 1;
    for (auto u : g[v]) {
        if (color[u] == 1) {
            cout << "No";
            exit(0);
        } else if (color[u] == 0) {
            dfs(u);
        }
    }
    color[v] = 2;
    topsort.pb(v);
}

void paint(int v) {
    color[v] = true;
    comp[v] = col;
    for (auto u : g[v]) {
        if (!color[u]) {
            paint(u);
        }
    }
}

void check(int n, vector<string>& nums) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] == nums[j] || nums[i].size() > nums[j].size()) {
                cout << "NO";
                exit(0);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[i].size() > 1) {
            cant_be_zero.insert(nums[i][0] - 'a');
        }
    }
    check(n, nums);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && nums[j].size() == nums[i].size(); j++) {
            for (size_t k = 0; k < nums[i].size(); k++) {
                if (nums[i][k] != nums[j][k]) {
                    g[(int)(nums[i][k] - 'a')].pb((int)(nums[j][k] - 'a'));
                    break;
                }
            }
        }
    }
    set<int> free;
    for (int i = 0; i < 26; i++) {
        if (color[i] == 0) {
            dfs(i);
        }
        free.insert(i);
    }
    fill(color.begin(), color.end(), 0);
    cout << "Yes\n";
    reverse(topsort.begin(), topsort.end());
    for (int i = 0; i < 26; i++) {
        if (color[i] == 0) {
            col++;
            paint(i);
        }
    }
    vector<int> ans(26);
    for (size_t i = 0; i < topsort.size();) {
        int cur = comp[topsort[i]];
        int k = i;
        while (i < topsort.size() && comp[topsort[i]] == cur) {
            size_t p = cant_be_zero.count(topsort[k]) && *free.begin() == 0;
            if (p == free.size()) {
                cout << "No";
                return 0;
            }
            size_t cnt = 0;
            for (auto u : free) {
                if (cnt == p) {
                    ans[topsort[i]] = u;
                    free.erase(ans[topsort[i]]);
                    break;
                }
                cnt++;
            }
            i++;
        }
    }
    for (int i = 0; i < 26; i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}
