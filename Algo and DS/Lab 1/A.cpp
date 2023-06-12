#include <iostream>
using namespace std;

struct Vector {
    int *a = new int[0], r = 0, sz = 0;

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

    Vector a;
    int n;
    cin >> n;
    while (n--) {
        char c;
        cin >> c;
        if (c == '+') {
            int x;
            cin >> x;
            a.push(x);
        } else {
            cout << a.top() << endl;
            a.pop();
        }
    }
    return 0;
}
