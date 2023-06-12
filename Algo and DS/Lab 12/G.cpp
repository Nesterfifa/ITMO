#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 1e9 + 7;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 6e18;

struct Node {
    Node* children[26];
    Node* go[26];
    Node* p;
    Node* link;
    Node* up;
    char c;
    bool leaf;
    vector<int> ends;

    Node() : p(0), link(0), up(0), leaf(0) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
            go[i] = nullptr;
        }
    };
};

Node *root = new Node();

void add_string(string s, int idx) {
    Node* node = root;
    for (auto u : s) {
        if (!node->children[u - 'a']) {
            node->children[u - 'a'] = new Node();
            node->children[u - 'a']->p = node;
            node->children[u - 'a']->c = u;
            node->children[u - 'a']->leaf = false;
        }
        node = node->children[u - 'a'];
    }
    node->leaf = true;
    node->ends.pb(idx);
}

Node* link(Node* node, char c);

Node* suff_link(Node* node) {
    if (!node->link) {
        if (node == root || node->p == root) {
            node->link = root;
        } else {
            node->link = link(suff_link(node->p), node->c);
        }
    }
    return node->link;
}

Node* link(Node* node, char c) {
    if (!node->go[c - 'a']) {
        if (node->children[c - 'a']) {
            node->go[c - 'a'] = node->children[c - 'a'];
        } else if (node == root) {
            node->go[c - 'a'] = root;
        } else {
            node->go[c - 'a'] = link(suff_link(node), c);
        }
    }
    return node->go[c - 'a'];
}

Node* get_up(Node* node) {
    if (!node->up) {
        if (suff_link(node)->leaf) {
            node->up = suff_link(node);
        } else if (suff_link(node) == root) {
            node->up = root;
        } else {
            node->up = get_up(suff_link(node));
        }
    }
    return node->up;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        add_string(s, i);
    }
    string t;
    cin >> t;
    vector<string> ans(m, "NO");
    Node* cur = root;
    for (int i = 0; i < (int)t.size(); i++) {
        char c = t[i];
        cur = link(cur, c);
        for (auto u : cur->ends) {
            ans[u] = "YES";
        }
        cur->ends.clear();
        Node* node = get_up(cur);
        while (node != root) {
            for (auto u : node->ends) {
                ans[u] = "YES";
            }
            node->ends.clear();
            Node* node1 = node;
            node = get_up(node);
            node1->up = root;
        }
    }
    for (auto u : ans) {
        cout << u << endl;
    }
    return 0;
}
