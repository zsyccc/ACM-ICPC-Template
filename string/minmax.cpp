#include <algorithm>
using namespace std;

// T = sec[k..n-1]+sec[0..k-1]
// k为返回值,n为sec的大小,T为sec的最小表示法
int get_min(const char* sec, int n) {
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
        if (sec[(i + k) % n] == sec[(j + k) % n]) {
            k++;
        } else {
            sec[(i + k) % n] > sec[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    i = min(i, j);
    return i;
}

int get_max(const char* sec, int n) {
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
        if (sec[(i + k) % n] == sec[(j + k) % n]) {
            k++;
        } else {
            sec[(i + k) % n] < sec[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    i = min(i, j);
    return i;
}