#include <iostream>
using namespace std;

struct Vector {
    int *a = new int[0];
    int r = 0, sz = 0;

    void push(int x) {
        if (sz == 0) {
            a = new int[1];
            a[r++] = x;
            sz = 1;
        } else {
            if (r == sz) {
                int *b = a;
                a = new int[sz * 2];
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

int to_int(string s) {
    int x = 0;
    for (int i = 0; i < (int)s.length(); i++)
        x = 10 * x + s[i] - '0';
    return x;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Vector a;
    string c;
    while (cin >> c) {
        if (isdigit(c[0])) {
            a.push(to_int(c));
        } else {
            int y = a.top();
            a.pop();
            int x = a.top();
            a.pop();
            if (c[0] == '+') {
                a.push(x + y);
            }
            if (c[0] == '*') {
                a.push(x * y);
            }
            if (c[0] == '-') {
                a.push(x - y);
            }
        }
    }
    cout << a.top();
    return 0;
}
