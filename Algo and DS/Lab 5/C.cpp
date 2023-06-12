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
    int y, sz, val;
    Node *l, *r;
};

Node *new_node(int x) {
    Node *node = new Node;
    node->y = rand();
    node->sz = 1;
    node->val = x;
    node->l = node->r = nullptr;
    return node;
}

int get_sz(Node *t) {
    if (t) {
        return t->sz;
    }
    return 0;
}

void update_sz(Node *t) {
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
        update_sz(t1);
        return t1;
    } else {
        t2->l = merge(t1, t2->l);
        update_sz(t2);
        return t2;
    }
}

void split(Node *t, int x, Node *&t1, Node *&t2) {
    if (!t) {
        t1 = t2 = nullptr;
        return;
    }
    if (get_sz(t->l) < x) {
        split(t->r, x - get_sz(t->l) - 1, t->r, t2);
        t1 = t;
    } else {
        split(t->l, x, t1, t->l);
        t2 = t;
    }
    update_sz(t);
}

Node *add(Node *t, int pos, int x) {
    Node *t1, *t2;
    split(t, pos, t1, t2);
    Node *node = new_node(x);
    return merge(merge(t1, node), t2);
}

Node *remove(Node *t, int pos) {
    Node *t1, *t2, *t3, *t4;
    split(t, pos, t1, t2);
    split(t2, 1, t3, t4);
    t = merge(t1, t4);
    delete t3;
    return t;
}

Node *build(vector<int> &a) {
    Node *res = nullptr;
    for (auto i : a) {
        res = merge(res, new_node(i));
    }
    return res;
}

Node *move_to_begin(Node *t, int l, int r) {
    Node *t1, *t2, *t3, *t4;
    split(t, r + 1, t1, t2);
    split(t1, l, t3, t4);
    return merge(merge(t4, t3), t2);
}

void write(Node *t) {
    if (t == nullptr) {
        return;
    }
    write(t->l);
    cout << t->val << " ";
    write(t->r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.pb(i + 1);
    }
    Node *t = build(a);
    while (m--) {
        int l, r;
        cin >> l >> r;
        r--; l--;
        t = move_to_begin(t, l, r);
    }
    write(t);
    return 0;
}
