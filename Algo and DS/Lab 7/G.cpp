#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define first (get<0>)
#define second (get<1>)
#define third (get<2>)

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 3e18;

ll a[200000];
tuple<ll, ll, ll> t[800000];

void build(int v, int l, int r) {
    third(t[v]) = -INFLL;
    if (l == r) {
        first(t[v]) = a[l];
    } else {
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m);
        build(v * 2 + 2, m + 1, r);
        first(t[v]) = min(first(t[v * 2 + 1]), first(t[v * 2 + 2]));
    }
}

void push_add(int v) {
    second(t[v * 2 + 1]) += second(t[v]);
    second(t[v * 2 + 2]) += second(t[v]);
    second(t[v]) = 0;
}

void push_set(int v) {
    if (third(t[v]) != -INFLL) {
        first(t[v * 2 + 1]) = first(t[v * 2 + 2]) = third(t[v]);
        third(t[v * 2 + 1]) = third(t[v * 2 + 2]) = third(t[v]);
        second(t[v * 2 + 1]) = second(t[v * 2 + 2]) = 0;
        third(t[v]) = -INFLL;
    }
}

void set_seg(int v, int l, int r, int L, int R, ll val) {
    if (L > R) {
        return;
    }
    if (L == l && r == R) {
        first(t[v]) = third(t[v]) = val;
        second(t[v]) = 0;
        return;
    }
    push_set(v);
    push_add(v);
    int m = (l + r) / 2;
    set_seg(v * 2 + 1, l, m, L, min(m, R), val);
    set_seg(v * 2 + 2, m + 1, r, max(L, m + 1), R, val);
    first(t[v]) = min(first(t[v * 2 + 1]) + second(t[v * 2 + 1]),
            first(t[v * 2 + 2]) + second(t[v * 2 + 2]));
}

void add(int v, int l, int r, int L, int R, ll val) {
    if (L > R) {
        return;
    }
    push_set(v);
    if (l == L && r == R) {
        second(t[v]) += val;
        return;
    }
    int m = (l + r) / 2;
    add(v * 2 + 1, l, m, L, min(m, R), val);
    add(v * 2 + 2, m + 1, r, max(L, m + 1), R, val);
    first(t[v]) = min(first(t[v * 2 + 1]) + second(t[v * 2 + 1]),
            first(t[v * 2 + 2]) + second(t[v * 2 + 2]));
}

ll get_min(int v, int l, int r, int L, int R) {
    if (L > R) {
        return INFLL;
    }
    push_set(v);
    if (l == L && r == R) {
        return first(t[v]) + second(t[v]);
    }
    int m = (l + r) / 2;
    return second(t[v]) + min(get_min(v * 2 + 1, l, m, L, min(m, R)),
            get_min(v * 2 + 2, m + 1, r, max(L, m + 1), R));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, 0, n - 1);
    string req;
    while (cin >> req) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        if (req == "set") {
            ll x;
            cin >> x;
            set_seg(0, 0, n - 1, l, r, x);
        } else if (req == "add") {
            ll x;
            cin >> x;
            add(0, 0, n - 1, l, r, x);
        } else {
            cout << get_min(0, 0, n - 1, l, r) << endl;
        }
    }
    return 0;
}
