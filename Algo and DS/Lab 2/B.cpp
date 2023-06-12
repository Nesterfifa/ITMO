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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    int m;
    cin >> m;
    while (m--) {
        int x;
        cin >> x;
        int l = 0, r = n - 1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (a[mid] < x) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if (a[l] == x) {
            cout << l + 1 << ' ';
        } else if (a[r] == x) {
            cout << r + 1 << ' ';
        } else {
            cout << -1 << ' ';
        }
        l = 0, r = n - 1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (a[mid] <= x) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if (a[r] == x) {
            cout << r + 1 << ' ' << endl;
        } else if (a[l] == x) {
            cout << l + 1 << ' ' << endl;
        } else {
            cout << -1 << ' ' << endl;
        }
    }
    return 0;
}
