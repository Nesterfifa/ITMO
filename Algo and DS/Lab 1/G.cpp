#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back
#define ins insert

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 1e9 + 9;
const int INF = 1e9;
const ll INFLL = 3e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k; int a, b, c;
    ll ans = 0;
    cin >> n >> m >> k >> a >> b >> c;
    stack<pair<int, int> > left, right;
    int v[1000];
    for (int i = 0; i < k; i++) {
        cin >> v[i];
        if (i < m) {
            if (left.empty()) {
                left.push({v[i], v[i]});
            } else {
                left.push({v[i], min(v[i], left.top().second)});
            }
        }
    }
    int l1 = v[k - 2], l2 = v[k - 1];
    if (k < m) {
        for (int i = k; i < m; i++) {
           if (left.empty()) {
                left.push({(int)(a * l1 + b * l2 + c), (int)(a * l1 + b * l2 + c)});
            } else {
                left.push({a * l1 + b * l2 + c, min(a * l1 + b * l2 + c, left.top().second)});
            }
            int x = l2;
            l2 = (int)(a * l1 + b * l2 + c);
            l1 = x;
        }
    }
    int r = m;
    for (int i = 0; i + m - 1 < n; i++) {
        if (left.empty()) {
            ans += right.top().second;
        } else {
            if (right.empty()) {
                ans += left.top().second;
            } else {
                ans += min(left.top().second, right.top().second);
            }
        }
        if (right.empty()) {
            while (!left.empty()) {
                if (right.empty()) {
                    right.push({left.top().first, left.top().first});
                } else {
                    right.push({left.top().first, min(left.top().first, right.top().second)});
                }
                left.pop();
            }
        }
        right.pop();
        if (r >= k) {
            if (left.empty()) {
                left.push({(int)(a * l1 + b * l2 + c), (int)(a * l1 + b * l2 + c)});
            } else {
                left.push({a * l1 + b * l2 + c, min(a * l1 + b * l2 + c, left.top().second)});
            }
            int x = l2;
            l2 = (int)(a * l1 + b * l2 + c);
            l1 = x;
        } else {
            if (left.empty()) {
                left.push({v[r], v[r]});
            } else {
                left.push({v[r], min(v[r], left.top().second)});
            }
            r++;
        }
    }
    cout << ans;
    return 0;
}
