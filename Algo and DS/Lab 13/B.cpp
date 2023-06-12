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

vector<int> suf_arr(string &s) {
    int n = s.size();
    vector<int> p(400001), cnt(400001), c(400001), pn(400001), cn(400001);
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
        c = vector<int>(cn);
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    s.pb('#');
    vector<int> sarr = suf_arr(s);
    for (int i = 1; i < (int)s.size(); i++) {
        cout << sarr[i] + 1 << ' ';
    }
    return 0;
}
