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

void merge(int a[], int l, int r) {
    vector<int> b, c;
    for (int i = l; i <= (l + r) / 2; i++) {
        b.pb(a[i]);
    }
    for (int i = (r + l) / 2 + 1; i <= r; i++) {
        c.pb(a[i]);
    }
    int L = 0, R = 0;
    while (L < (int)b.size() || R < (int)c.size()) {
        if (L == (int)b.size()) {
            a[l++] = c[R++];
        } else if (R == (int)c.size()) {
            a[l++] = b[L++];
        } else if (b[L] < c[R]) {
            a[l++] = b[L++];
        } else {
            a[l++] = c[R++];
        }
    }
}

void mergesort(int a[], int l, int r) {
    if (l == r) {
        return;
    }
    int m = (l + r) / 2;
    mergesort(a, l, m);
    mergesort(a, m + 1, r);
    merge(a, l, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    int a[300000];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    mergesort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    return 0;
}
