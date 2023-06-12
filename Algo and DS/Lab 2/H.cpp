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

long long ans = 0;
int arr[1000010];

void merge(int a[], int l, int r) {
    vector<int> b, c;
    for (int i = l; i <= (l + r) / 2; i++) {
        b.pb(a[i]);
    }
    for (int i = (r + l) / 2 + 1; i <= r; i++) {
        c.pb(a[i]);
        int L = 0, R = b.size() - 1;
        while (R > L + 1) {
            int m = (L + R) / 2;
            if (b[m] > a[i]) {
                R = m;
            } else {
                L = m;
            }
        }
        if (b[L] > a[i]) {
            ans += (int)b.size() - L;
        } else if (b[R] > a[i]) {
            ans += (int)b.size() - R;
        }
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

    int n, m; unsigned int a, b;
    cin >> n >> m >> a >> b;
    unsigned int cur = 0;
    for (int i = 0; i < n; i++) {
        cur = cur * a + b;
        arr[i] = (cur >> 8) % m;
    }
    mergesort(arr, 0, n - 1);
    cout << ans;
    return 0;
}
