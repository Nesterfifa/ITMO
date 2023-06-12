#include <iostream>
#include <chrono>
#include <omp.h>
#include <vector>
#include <random>
#include <cassert>
#include <functional>
#include <climits>

using namespace std;

const int n = 1e8;
random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> small_rand_int(0, 100);

pair<int, int> partition_seq(vector<int> &a, int l, int r) {
    int pivot = a[(l + r) / 2];
    int midLeft = l;
    for (int i = l; i < r; i++) {
        if (a[i] < pivot) {
            swap(a[i], a[midLeft]);
            midLeft++;
        }
    }
    int midRight = midLeft;
    for (int i = midLeft; i < r; i++) {
        if (a[i] == pivot) {
            swap(a[i], a[midRight]);
            midRight++;
        }
    }
    return {midLeft, midRight};
}

void quick_sort_seq(vector<int> &a, int l, int r) {
    if (l + 1 >= r) {
        return;
    }
    pair<int, int> p = partition_seq(a, l, r);
    quick_sort_seq(a, l, p.first);
    quick_sort_seq(a, p.second, r);
}

void quick_sort_par(vector<int> &a, int l, int r) {
    if (l + 1 >= r) {
        return;
    }
    if (r - l < n / log(n)) {
        quick_sort_seq(a, l, r);
        return;
    }
    pair<int, int> p = partition_seq(a, l, r);
#pragma omp task shared(a)
    {
        quick_sort_par(a, l, p.first);
    }
#pragma omp task shared(a)
    {
        quick_sort_par(a, p.second, r);
    }
}

long long bench_seq(vector<int> a) {
    auto start = chrono::steady_clock::now();
    quick_sort_seq(a, 0, n);
    auto stop = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "SEQ: " << duration.count() << "ms" << endl;
    return duration.count();
}

long long bench_par(vector<int> a) {
    omp_set_num_threads(4);
    omp_set_nested(2);
    auto start = chrono::steady_clock::now();
#pragma omp parallel shared(a)
    {
#pragma omp single
        {
            quick_sort_par(a, 0, n);
        }
    }

    auto stop = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "PAR: " << duration.count() << "ms" << endl << endl;
    return duration.count();
}

bool is_sorted(vector<int> &a) {
    for (int i = 0; i < a.size() - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

bool both_correct() {
    bool ans = true;
    for (int t = 0; t < 3; t++) {
        vector<int> a(n);
        for (int &k: a) {
            k = small_rand_int(rng);
        }
        quick_sort_seq(a, 0, n);
        ans &= is_sorted(a);
    }
    for (int t = 0; t < 3; t++) {
        vector<int> a(n);
        for (int &k: a) {
            k = small_rand_int(rng);
        }
        quick_sort_par(a, 0, n);
        ans &= is_sorted(a);
    }
    return ans;
}

int main() {
    assert(both_correct());

    double sum_seq = 0;
    double sum_par = 0;

    for (int i = 0; i < 5; i++) {
        vector<int> a(n);
        for (int &k: a) {
            k = (int)rand();
        }
        sum_seq += bench_seq(a);
        sum_par += bench_par(a);
    }
    cout << "Seq avg: " << sum_seq / 5 << endl;
    cout << "Par avg: " << sum_par / 5 << endl;
    cout << "Score: " << sum_seq / sum_par;
    return 0;
}

