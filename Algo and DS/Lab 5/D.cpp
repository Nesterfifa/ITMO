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

    Node *l, *r;

    Node(int _x) {
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

void update(Node *&t) {
    if (!t) {
        return;
    }
    t->sz = 1 + get_sz(t->l) + get_sz(t->r);
}

Node *merge(Node *t1, Node *t2) {
    if (!t1) {
        return t2;
    }
    if (!t2) {
        return t1;
    }
    if (t1->y > t2->y) {
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
    Node *t1, *t2;
    split(t, x, t1, t2);
    t = merge(merge(t1, new Node(x)), t2);
}

void remove(Node *&t, int x) {
    Node *t1, *t2, *t3, *t4;
    split(t, x, t1, t2);
    split(t2, x + 1, t3, t4);
    t = merge(t1, t4);
    delete t3;
}

int get_k(Node *t, int k) {
    if (k < get_sz(t->l)) {
        return get_k(t->l, k);
    } else if (k == get_sz(t->l)) {
        return t->x;
    } else {
        return get_k(t->r, k - get_sz(t->l) - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    Node *t = nullptr;
    while (n--) {
        string s; int x;
        cin >> s >> x;
        if (s == "+1" || s == "1") {
            add(t, x);
        } else if (s == "0") {
            cout << get_k(t, get_sz(t) - x) << endl;
        } else {
            remove(t, x);
        }
    }
    return 0;
}
