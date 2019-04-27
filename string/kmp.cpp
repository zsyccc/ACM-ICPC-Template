#include <bits/stdc++.h>

using namespace std;

const int maxn = 10000 + 5;

int f[maxn];

void get_next(int *P, int n) {
    f[0] = 0;
    f[1] = 0;  // 递推边界初值
    for (int i = 1; i < n; i++) {
        int j = f[i];
        while (j && P[i] != P[j]) j = f[j];
        f[i + 1] = (P[i] == P[j] ? j + 1 : 0);
    }
}
