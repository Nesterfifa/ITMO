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

pair<int, int> t[400000];

void build(int v, int l, int r) {
    if (l == r) {
        t[v].x = l;
        return;
    }
    int m = (l + r) / 2;
    build(v * 2 + 1, l, m);
    build(v * 2 + 2, m + 1, r);
    t[v].x = l;
}

void exit(int v, int l, int r, int pos) {
    if (l == r) {
        t[v].x = l;
        t[v].y = 0;
        return;
    }
    int m = (l + r) / 2;
    if (pos <= m) {
        exit(v * 2 + 1, l, m, pos);
    } else {
        exit(v * 2 + 2, m + 1, r, pos);
    }
    t[v].x = INF;
    if (t[v * 2 + 1].y == 0 && t[v * 2 + 1].x < t[v].x) {
        t[v].x = t[v * 2 + 1].x;
    }
    if (t[v * 2 + 2].y == 0 && t[v * 2 + 2].x < t[v].x) {
        t[v].x = t[v * 2 + 2].x;
    }
}

void enter(int v, int l, int r, int pos) {
    if (l == r) {
        t[v].x = INF;
        t[v].y = 1;
        return;
    }
    int m = (l + r) / 2;
    if (pos <= m) {
        enter(v * 2 + 1, l, m, pos);
    } else {
        enter(v * 2 + 2, m + 1, r, pos);
    }
    t[v].x = INF;
    if (t[v * 2 + 1].y == 0 && t[v * 2 + 1].x < t[v].x) {
        t[v].x = t[v * 2 + 1].x;
    }
    if (t[v * 2 + 2].y == 0 && t[v * 2 + 2].x < t[v].x) {
        t[v].x = t[v * 2 + 2].x;
    }
}

int find_free(int v, int l, int r, int L, int R) {
    if (L > R) {
        return INF;
    }
    if (l == L && r == R) {
        return t[v].x;
    }
    int m = (l + r) / 2;
    return min(find_free(v * 2 + 1, l, m, L, min(m, R)),
            find_free(v * 2 + 2, m + 1, r, max(L, m + 1), R));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    build(0, 0, n - 1);
    string s;
    int pos;
    while (cin >> s >> pos) {
        pos--;
        if (s == "exit") {
            exit(0, 0, n - 1, pos);
        } else {
            int real = find_free(0, 0, n - 1, pos, n - 1);
            if (real == INF) {
                real = find_free(0, 0, n - 1, 0, pos - 1);
            }
            cout << real + 1 << endl;
            enter(0, 0, n - 1, real);
        }
    }
    return 0;
}
