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

struct matrix {
    int data[2][2];

    matrix() {
        data[0][0] = data[1][1] = data[1][0] = data[0][1] = 0;
    }

    void print() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cout << data[i][j] << ' ';
            }
            cout << endl;
        }
    }

    void read() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cin >> data[i][j];
            }
        }
    }
};

int MOD;
matrix* ans = new matrix();

void matrix_mul(matrix *&a, matrix *b) {
    int a1 = a->data[0][0] * b->data[0][0] + a->data[0][1] * b->data[1][0];
    int a2 = a->data[0][0] * b->data[0][1] + a-> data[0][1] * b->data[1][1];
    int a3 = a->data[1][0] * b->data[0][0] + a->data[1][1] * b->data[1][0];
    int a4 = a->data[1][0] * b->data[0][1] + a->data[1][1] * b->data[1][1];
    a->data[0][0] = a1 % MOD;
    a->data[0][1] = a2 % MOD;
    a->data[1][0] = a3 % MOD;
    a->data[1][1] = a4 % MOD;
}

matrix *a[200000], *t[800000];

void build(int v, int l, int r) {
    if (l == r) {
        t[v] = a[l];
    } else {
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m);
        build(v * 2 + 2, m + 1, r);
        t[v] = new matrix();
        t[v]->data[0][0] = t[v]->data[1][1] = 1;
        matrix_mul(t[v], t[v * 2 + 1]);
        matrix_mul(t[v], t[v * 2 + 2]);
    }
}

void mul(int v, int l, int r, int L, int R) {
    if (L > R) {
        return;
    }
    if (l == L && r == R) {
        matrix_mul(ans, t[v]);
        return;
    }
    int m = (l + r) / 2;
    mul(v * 2 + 1, l, m, L, min(m, R)),
    mul(v * 2 + 2, m + 1, r, max(L, m + 1), R);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> MOD >> n >> m;
    for (int i = 0; i < n; i++) {
        a[i] = new matrix();
        a[i]->read();
    }
    build(0, 0, n - 1);
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        ans->data[0][0] = ans->data[1][1] = 1;
        ans->data[1][0] = ans->data[0][1] = 0;
        mul(0, 0, n - 1, l, r);
        ans->print();
        cout << endl;
    }
    return 0;
}
