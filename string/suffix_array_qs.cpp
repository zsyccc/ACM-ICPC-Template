#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

namespace SuffixArray {
    using std::printf;

    const int maxn = 1e7 + 5;  // max(字符串长度，最大字符值加1)

    int s[maxn];                       // 原始字符数组（最后一个字符应必须是0，而前面的字符必须非0）
    int sa[maxn];                      // 后缀数组
    int t[maxn], rank[maxn], c[maxn];  // 辅助数组
    int n;                             // 字符个数（包括最后一个0字符）

    void init() { n = 0; }

    int k;
    bool compare_sa(int i, int j) {
        if (rank[i] != rank[j]) {
            return rank[i] < rank[j];
        } else {
            int ri = i + k < n ? rank[i + k] : -1;
            int rj = j + k < n ? rank[j + k] : -1;
            return ri < rj;
        }
    }

    void build_sa(int _) {
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = i < n ? s[i] : -1;
        }
        for (k = 1; k < n; k <<= 1) {
            sort(sa, sa + n, compare_sa);
            t[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                t[sa[i]] = t[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
            }
            for (int i = 0; i < n; i++) {
                rank[i] = t[i];
            }
        }
    }

    int height[maxn];  // height数组
    void build_height() {
        int i, k = 0;
        for (i = 0; i < n; i++) {
            if (k) k--;
            int j = sa[rank[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            height[rank[i]] = k;
        }
    }
}  // namespace SuffixArray