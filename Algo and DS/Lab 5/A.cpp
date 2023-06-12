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
    int key;
    Node *left, *right;

    Node() {}

    Node(int x) {
        key = x;
        left = right = nullptr;
    }
};

Node *exists(Node *t, int key) {
    if (t == nullptr || key == t->key) {
        return t;
    }
    if (key < t->key) {
        return exists(t->left, key);
    } else {
        return exists(t->right, key);
    }
}

Node *get_min(Node *t) {
    if (t->left == nullptr) {
        return t;
    }
    return get_min(t->left);
}

Node *get_max(Node *t) {
    if (t->right == nullptr) {
        return t;
    }
    return get_max(t->right);
}

Node *next(Node *t, int x) {
    Node *cur = t, *ans = nullptr;
    while (cur != nullptr) {
        if (cur -> key > x) {
            ans = cur;
            cur = cur -> left;
        } else {
            cur = cur -> right;
        }
    }
    return ans;
}

Node *prev(Node *t, int x) {
    Node *cur = t, *ans = nullptr;
    while (cur != nullptr) {
        if (cur -> key < x) {
            ans = cur;
            cur = cur -> right;
        } else {
            cur = cur -> left;
        }
    }
    return ans;
}

Node *insert(Node *x, int t) {
    if (x == nullptr) {
        return new Node(t);
    } else if (t < x->key) {
        x->left = insert(x->left, t);
    } else if (t > x->key) {
        x->right = insert(x->right, t);
    }
    return x;
}

Node *remove(Node *t, int x) {
    if (t == nullptr) {
        return t;
    }
    if (x < t->key) {
        t->left = remove(t->left, x);
    } else if (x > t->key) {
        t->right = remove(t->right, x);
    } else if (t->left != nullptr && t->right != nullptr) {
        t->key = get_min(t->right)->key;
        t->right = remove(t->right, t->key);
    } else {
        if (t->left != nullptr) {
            t = t->left;
        } else if (t->right != nullptr) {
            t = t->right;
        } else {
            t = nullptr;
        }
    }
    return t;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s; int x;
    Node *t = nullptr;
    while (cin >> s) {
        cin >> x;
        if (s == "insert") {
            t = insert(t, x);
        } else if (s == "delete") {
            t = remove(t, x);
        } else if (s == "exists") {
            if (exists(t, x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (s == "prev") {
            Node *ans = prev(t, x);
            if (ans == nullptr) {
                cout << "none\n";
            } else {
                cout << ans -> key << endl;
            }
        } else if (s == "next") {
            Node *ans = next(t, x);
            if (ans == nullptr) {
                cout << "none\n";
            } else {
                cout << ans -> key << endl;
            }
        }
    }
    return 0;
}
