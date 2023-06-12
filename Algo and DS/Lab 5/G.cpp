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
const int mod1 = 999999937;
const int INF = 1e9;
const ll INFLL = 3e18;

struct Node {
    int x, y, sz;
    ll sum;

    Node *l, *r;

    Node(int _x) {
        sum = _x;
        x = _x;
        y = rand();
        sz = 1;
        l = r = nullptr;
    }
};

int get_sz(Node *t) {
    if (!t) {
        return 0;
    }
    return t->sz;
}

ll get_sum(Node *t) {
    if (!t) {
        return 0;
    }
    return t->sum;
}

void update(Node *&t) {
    if (!t) {
        return;
    }
    t->sz = 1 + get_sz(t->l) + get_sz(t->r);
    t->sum = t->x + get_sum(t->l) + get_sum(t->r);
}

Node *merge(Node *t1, Node *t2) {
    if (!t1) {
        return t2;
    }
    if (!t2) {
        return t1;
    }
    if (t1->y < t2->y) {
        t1->r = merge(t1->r, t2);
        update(t1);
        return t1;
    } else {
        t2->l = merge(t1, t2->l);
        update(t2);
        return t2;
    }
}

void split(Node *t, int x, Node *&t1, Node *&t2) {
    if (!t) {
        t1 = t2 = nullptr;
        return;
    }
    if (t->x < x) {
        split(t->r, x, t->r, t2);
        t1 = t;
    } else {
        split(t->l, x, t1, t->l);
        t2 = t;
    }
    update(t);
}

void add(Node *&t, int x) {
    Node *t1, *t2, *t3, *t4;
    split(t, x, t1, t2);
    split(t2, x + 1, t3, t4);
    if (get_sz(t3) == 1) {
        t = merge(t1, merge(t3, t4));
    } else {
        t = merge(merge(t1, new Node(x)), t4);
    }
}

void remove(Node *&t, int x) {
    Node *t1, *t2, *t3, *t4;
    split(t, x, t1, t2);
    split(t2, x + 1, t3, t4);
    t = merge(t1, t4);
    delete t3;
}

ll get_ans(Node *t, int l, int r) {
    Node *t1, *t2, *t3, *t4;
    split(t, r + 1, t1, t2);
    split(t1, l, t3, t4);
    ll ans = get_sum(t4);
    t = merge(merge(t3, t4), t2);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    Node *t = nullptr;
    ll last_ans = 0;
    while (n--) {
        char c;
        cin >> c;
        if (c == '+') {
            ll x;
            cin >> x;
            add(t, (int)((x + last_ans) % 1000000000ll));
            last_ans = 0;
        } else {
            int l, r;
            cin >> l >> r;
            last_ans = get_ans(t, l, r);
            cout << last_ans << endl;
        }
    }
    return 0;
}
