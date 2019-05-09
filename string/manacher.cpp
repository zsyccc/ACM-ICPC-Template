#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000000;
int d1[maxn], d2[maxn];

// s 为字符串,也可以是const string&
// n 是字符串长度,即为s.length()
// d1为奇数回文长度(算上起点),总长度为d1[.]*2-1
// d2为偶数回文长度(算上起点),总长度为d2[.]*2
void Manacher(const char* s, int n) {
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}

// 判断[l,r)是否回文
bool is_palindrome(int l, int r) {
    if (l == r) return true;
    if ((r - l) & 1) {
        return d1[l + (r - l) / 2] >= (r - l + 1) / 2;
    } else {
        return d2[l + (r - l) / 2] >= (r - l) / 2;
    }
}