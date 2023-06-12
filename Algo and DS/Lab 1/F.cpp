#include <iostream>
using namespace std;

struct Vector {
    char *a = new char[0];
    int r = 0, sz = 0;

    void push(char x) {
        if (sz == 0) {
            a = new char[1];
            a[r++] = x;
            sz = 1;
        } else {
            if (r == sz) {
                char *b = a;
                a = new char[sz * 2];
                for (int i = 0; i < sz; i++)
                    a[i] = b[i];
                delete b;
                sz *= 2;
                a[r++] = x;
            } else {
                a[r++] = x;
            }
        }
    }

    bool empty() {
        return (r == 0);
    }

    void pop() {
        r--;
    }

    int top() {
        return a[r - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    while (getline(cin, s)) {
        Vector *a = new Vector;
        int flag = 1;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '[' || s[i] == '(') {
                (*a).push(s[i]);
            } else {
                if (s[i] == ']') {
                    if (!(*a).empty() && (*a).top() == '[') {
                        (*a).pop();
                    } else {
                        flag = 0;
                    }
                } else {
                    if (!(*a).empty() && (*a).top() == '(') {
                        (*a).pop();
                    } else {
                        flag = 0;
                    }
                }
            }
        }
        if (flag && (*a).empty()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        delete a;
    }
    return 0;
}
