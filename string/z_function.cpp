#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000000 + 5;

int z[maxn];

// s 为待匹配的字符串指针
// n 为字符串长度
// z[i]是s和s+i的最大公共前缀长度。
void z_function(const char* s, int n) {
    fill_n(z, n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}
