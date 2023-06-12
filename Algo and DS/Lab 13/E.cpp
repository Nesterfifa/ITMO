#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 1e9;
const ll INFLL = 6e18;

vector<int> lcp(150001);

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

vector<int> suf_arr(vector<int> &s) {
    int n = s.size();
    vector<int> p(150001), cnt(150001), c(150001), pn(150001), cn(150001);
    vector<int> lcpn(150001), lpos(150001), rpos(150001);
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
                lcpn[i] = min(n, (1 << t) + tree.get_min(0, 0, 150000, lpos[c[ls]], rpos[c[rs]] - 1));
            }
        }
        lcp = vector<int>(lcpn);
        c = vector<int>(cn);
    }
    for (int i = 0; i < n - 1; i++) {
        lcp[i] = min (lcp[i], min (n - p[i], n - p[i + 1]));
    }
    return p;
}

struct candidate {
    int cnt;
    int len;
    int index;

    candidate(int cnt, int len, int index) : cnt(cnt), len(len), index(index) {}
};

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    a.push_back(100);
    vector<int> sarr = suf_arr(a);
    vector<candidate> st;
    int max_len = n;
    int max_cnt = 1;
    int start = 0;
    for (int i = 0; i < n; i++) {
        int x = 1;
        while (!st.empty() && lcp[i] <= st.back().len) {
            candidate c = st.back();
            st.pop_back();
            x += c.cnt;
            if ((ll)x * (ll)c.len > (ll)max_cnt * (ll)max_len) {
                max_cnt = x;
                max_len = c.len;
                start = sarr[c.index];
            }
        }
        if (st.empty() || lcp[i] > st.back().len) {
            st.push_back(candidate(x, lcp[i], i));
        }
    }
    cout << (ll)max_len * (ll)max_cnt << endl << max_len << endl;
    for (int i = start; i < start + max_len; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
