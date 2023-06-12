#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define ins insert
#define x first
#define y second

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 3e18;

int a[500000], t[2000000];

void build(int v, int l, int r) {
    if (l == r) {
        t[v] = a[l];
    } else {
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m);
        build(v * 2 + 2, m + 1, r);
        t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

void update(int v, int l, int r, int pos, int value) {
    if (l == r) {
        t[v] = value;
    } else {
        int m = (l + r) / 2;
        if (pos <= m) {
            update(v * 2 + 1, l, m, pos, value);
        } else {
            update(v * 2 + 2, m + 1, r, pos, value);
        }
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
    return min(get_min(v * 2 + 1, l, m, L, min(m, R)),
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
    int l, r;
    while (cin >> req >> l >> r) {
        l--; r--;
        if (req == "min") {
            cout << get_min(0, 0, n - 1, l, r) << endl;
        } else {
            r++;
            update(0, 0, n - 1, l, r);
        }
    }
    return 0;
}
