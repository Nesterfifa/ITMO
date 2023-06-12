#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back

const double pi = 3.14159265359;
const double eps = 1e-9;
const int mod = 998244353;
const int mod1 = 999999937;
const int INF = 2e9;
const ll INFLL = 6e18;

int cnt_v = 0, cnt_e = 0;

struct Node {
    map<char, Node*> children;
    int number;

    Node() {
        for (char c = 'a'; c <= 'z'; c++) {
            children[c] = nullptr;
        }
        number = cnt_v++;
    }
};

Node* add(Node* root, string s) {
    Node* cur = root;
    for (auto c : s) {
        if (!cur->children[c]) {
            cur->children[c] = new Node();
            cnt_e++;
        }
        cur = cur->children[c];
    }
    return root;
}

void print(Node* root) {
    if (root == nullptr) {
        return;
    }
    for (char c = 'a'; c <= 'z'; c++) {
        if (root->children[c]) {
            cout << root->number + 1 << " " << root->children[c]->number + 1 << " " << c << endl;
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        if (root->children[c]) {
            print(root->children[c]);
        }
    }
}

Node* build(Node* root, string s) {
    root = new Node();
    int n = s.size();
    for (int i = 0; i < n; i++) {
        add(root, s.substr(i, n));
    }
    return root;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    Node* root = nullptr;
    root = build(root, s);
    cout << cnt_v << ' ' << cnt_e << endl;
    print(root);
    return 0;
}
