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

struct List {
    List *next;
    int value;

    List() {}

    List(int value) {
        this -> value = value;
        this -> next = nullptr;
    }
};

void push(List *&t, int x) {
    List *p = t;
    t = new List(x);
    t -> next = p;
}

void pop(List *&t) {
    List *p = t;
    t = t -> next;
    delete p;
}

int top(List *t) {
    return t -> value;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    List *left = nullptr; List *right = nullptr;
    while (n--) {
        char c;
        cin >> c;
        if (c == '+') {
            int x;
            cin >> x;
            push(left, x);
        } else {
            if (right == nullptr) {
                while (left != nullptr) {
                    push(right, top(left));
                    pop(left);
                }
            }
            cout << top(right) << endl;
            pop(right);
        }
    }
    return 0;
}
