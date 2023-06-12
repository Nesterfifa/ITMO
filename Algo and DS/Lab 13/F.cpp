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

vector<int> lcp(400001);

struct segtree {
    vector<int> t;

    segtree(vector<int>& v) {
        t.resize(v.size() * 4);
        build(v, 0, 0, v.size() - 1);
    };

    void build(vector<int>& a, int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
        } else {
            int m = (l + r) / 2;
            build(a, v * 2 + 1, l, m);
            build(a, v * 2 + 2, m + 1, r);
            t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }

    int get_min(int v, int l, int r, int L, int R) {
        if (L > R) {
            return INF;
        }
        if (l == L && r == R) {
            return t[v];
        }
        int m = (l + r) / 2;
        return min(get_min(v * 2 + 1, l, m, L, min(m, R)), get_min(v * 2 + 2, m + 1, r, max(L, m + 1), R));
    }
};

ll ans(string &s) {
    int n = s.size();
    vector<int> p(400001), cnt(400001), c(400001), pn(400001), cn(400001);
    vector<int> lcpn(400001), lpos(400001), rpos(400001);
    for (auto v : s) {
        cnt[v]++;
    }
    for (int i = 1; i <= 'z'; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < n; i++) {
        p[--cnt[s[i]]] = i;
    }
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        classes += s[p[i]] != s[p[i - 1]];
        c[p[i]] = classes - 1;
    }

    for (int t = 0; (1 << t) < n; t++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << t);
            pn[i] += n * (pn[i] < 0);
            lpos[c[p[i]]] = rpos[c[p[i]]] = i;
        }
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) {
            cnt[c[pn[i]]]++;
        }
        for (int i = 1; i < classes; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            int m1 = (p[i] + (1 << t)) % n;
            int m2 = (p[i - 1] + (1 << t)) % n;
            classes += c[p[i]] != c[p[i - 1]] || c[m1] != c[m2];
            cn[p[i]] = classes - 1;
        }
        segtree tree = segtree(lcp);
        for (int i = 0; i < n - 1; i++) {
            int l = p[i], r = p[i + 1];
            if (c[l] != c[r]) {
                lcpn[i] = lcp[rpos[c[l]]];
            } else {
                int ls = (l + (1 << t)) % n, rs = (r + (1 << t) % n);
                lcpn[i] = min(n, (1 << t) + tree.get_min(0, 0, 400000, lpos[c[ls]], rpos[c[rs]] - 1));
            }
        }
        lcp = vector<int>(lcpn);
        c = vector<int>(cn);
    }
    for (int i=0; i<n-1; ++i) {
        lcp[i] = min (lcp[i], min (n-p[i], n-p[i+1]));
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += n - 1 - p[i] - lcp[i];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    s.pb('#');
    cout << ans(s);
    return 0;
}
