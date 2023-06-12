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

double check(double a, double h, int n) {
    for (int i = 2; i < n; i++) {
        double x = h;
        h = 2 * h - a + 2;
        a = x;
        if (h <= 0) {
            return 0;
        }
    }
    return h;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n; double a;
    cin >> n >> a;
    double l = 0, r = 100000000000000;
    while (r - l > 0.0000001) {
        double m = (l + r) / 2;
        if (check(a, m, n)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << fixed << setprecision(2) << check(a, r, n);
    return 0;
}
