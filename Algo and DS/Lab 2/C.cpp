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

int partition(vector<int> &a, int l, int r) {
    int v = a[(l + r) / 2];
    int i = l, j = r;
    while (true) {
        while (a[i] < v) {
            i++;
        }
        while (a[j] > v) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap(a[i++], a[j--]);
    }
    if (v == a[i]) {
        return i;
    } else {
        return j;
    }
}

int kth(vector<int> &a, int k) {
    int l = 0, r = a.size() - 1;
    while (true) {
        int m = partition(a, l, r);
        if (m == k) {
            return a[m];
        } else if (k < m) {
            r = m;
        } else {
            l = m + 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(2);
    int A, B, C;
    cin >> A >> B >> C >> a[0] >> a[1];
    for (int i = 2; i < n; i++) {
        a.pb(A * a[a.size() - 2] + B * a.back() + C);
    }
    if ((A == 0 && B == 0) || (A == 0 && a[1] == 0) || (B == 0 && a[0] == 0)) {
        int b[] = {a[0], a[1], C};
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                if (b[i] > b[j]) {
                    swap(b[i], b[j]);
                }
            }
        }
        if (k >= 3) {
            cout << b[2];
        } else {
            cout << b[k - 1];
        }
        return 0;
    }
    random_shuffle(a.begin(), a.end());
    random_shuffle(a.rbegin(), a.rend());
    cout << kth(a, k - 1);
    return 0;
}
