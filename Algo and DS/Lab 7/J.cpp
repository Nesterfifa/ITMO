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

pair<int, int> t[(int)8e6 + 1];
int h[(int)8e6 + 1];

void init_h(int v, int l, int r) {
    if (l == r) {
        h[v] = l;
    } else {
        int m = (l + r) / 2;
        init_h(v * 2 + 1, l, m);
        init_h(v * 2 + 2, m + 1, r);
        h[v] = l;
    }
}

void add(int v, int l, int r, int L, int R, int val) {
    if (L > R) {
        return;
    }
    if (l == L && r == R) {
        t[v].y += val;
        return;
    }
    int m = (l + r) / 2;
    add(v * 2 + 1, l, m, L, min(m, R), val);
    add(v * 2 + 2, m + 1, r, max(L, m + 1), R, val);
    t[v].x = max(t[v * 2 + 1].x + t[v * 2 + 1].y, t[v * 2 + 2].x + t[v * 2 + 2].y);
    if (t[v].x == t[v * 2 + 1].x + t[v * 2 + 1].y) {
        h[v] = h[v * 2 + 1];
    } else {
        h[v] = h[v * 2 + 2];
    }
}

pair<int, int> get_max(int v, int l, int r, int L, int R) {
    if (L > R) {
        return {-INF, l};
    }
    if (l == L && r == R) {
        return {t[v].x + t[v].y, h[v]};
    }
    int m = (l + r) / 2;
    pair<int, int> a = get_max(v * 2 + 1, l, m, L, min(m, R)),
    b = get_max(v * 2 + 2, m + 1, r, max(L, m + 1), R);
    a.first += t[v].y;
    b.first += t[v].y;
    if (a.first > b.first) {
        return a;
    } else {
        return b;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    init_h(0, 0, 2000000);
    vector<pair<pair<int, int>, pair<int, int> > > pts;
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        y1 += 1000000, y2 += 1000000;
        pts.pb({{x1, 0}, {y1, y2}});
        pts.pb({{x2, 1}, {y1, y2}});
    }
    sort(pts.begin(), pts.end());
    pair<int, int> pt_ans; int ans = -1;
    for (int i = 0; i < 2 * n; i++) {
        if (pts[i].x.y == 0) {
            add(0, 0, 2000000, pts[i].y.x, pts[i].y.y, 1);
            if (get_max(0, 0, 2000000, 0, 2000000).x > ans) {
                ans = get_max(0, 0, 2000000, 0, 2000000).x;
                pt_ans = {pts[i].x.x, get_max(0, 0, 2000000, 0, 2000000).y};
            }
        } else {
            add(0, 0, 2000000, pts[i].y.x, pts[i].y.y, -1);
        }
    }
    cout << ans << endl << pt_ans.x << ' ' << pt_ans.y - 1000000;
    return 0;
}
