#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int uint;

#define pb push_back
#define ins insert

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 1e9 + 9;
const int INF = 1e9;
const ll INFLL = 3e18;

unsigned int cur = 0, a, b, n;

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int aa = nextRand24(), bb = nextRand24();
    return (aa << 8) ^ bb;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t >> n >> a >> b;
    vector<uint> v(n);
    while (t--) {
        for (auto &i : v) {
            i = nextRand32();
        }
        vector<uint> used(1 << 16), b(n);
        for (uint i = 0; i < n; i++) {
            used[v[i] % (1 << 16)]++;
        }
        int cnt = 0;
        for (uint i = 0; i < used.size(); i++) {
            int x = used[i];
            used[i] = cnt;
            cnt += x;
        }
        for (uint i = 0; i < n; i++) {
            b[used[v[i] % (1 << 16)]] = v[i];
            used[v[i] % (1 << 16)]++;
        }
        fill(used.begin(), used.end(), 0);
        for (uint i = 0; i < n; i++) {
            used[b[i] / (1 << 16)]++;
        }
        cnt = 0;
        for (uint i = 0; i < used.size(); i++) {
            int x = used[i];
            used[i] = cnt;
            cnt += x;
        }
        for (uint i = 0; i < n; i++) {
            v[used[b[i] / (1 << 16)]] = b[i];
            used[b[i] / (1 << 16)]++;
        }
        unsigned long long ans = 0;
        for (uint i = 0; i < n; i++) {
            ans += (unsigned long long)v[i] * (unsigned long long)(i + 1);
        }
        cout << ans << "\n";
    }
    return 0;
}
