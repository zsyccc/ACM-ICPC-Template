#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 40000 + 10;

// 字符串哈希（概率算法）
struct StringHash {
    const int x;  // 随便取
    unsigned long long H[maxn], xp[maxn];
    int n;
    StringHash() : x(123) {}
    // n为字符串长度
    void init(const char* s, int n) {
        this->n = n;
        H[n] = 0;
        for (int i = n - 1; i >= 0; i--) H[i] = H[i + 1] * x + (s[i] - 'a');
        xp[0] = 1;
        for (int i = 1; i <= n; i++) xp[i] = xp[i - 1] * x;
    }
    // 从i开始，长度为L的字串的hash
    unsigned long long getHash(int i, int L) const {
        return H[i] - H[i + L] * xp[L];
    }
};
