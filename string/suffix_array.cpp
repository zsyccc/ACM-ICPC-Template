#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

namespace SuffixArray {
    using std::printf;

    const int maxn = 1e7 + 5;  // max(字符串长度，最大字符值加1)

    int s[maxn];                     // 原始字符数组（最后一个字符应必须是0，而前面的字符必须非0）
    int sa[maxn];                    // 后缀数组
    int rank[maxn];                  // 名次数组. rank[0]一定是n-1，即最后一个字符
    int height[maxn];                // height数组
    int t[maxn], t2[maxn], c[maxn];  // 辅助数组
    int n;                           // 字符个数（包括最后一个0字符）

    void init() { n = 0; }

    // m为最大字符值加1。调用之前需设置好s和n
    void build_sa(int m) {
        int i, *x = t, *y = t2;
        for (i = 0; i < m; i++) c[i] = 0;
        for (i = 0; i < n; i++) c[x[i] = s[i]]++;
        for (i = 1; i < m; i++) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (i = n - k; i < n; i++) y[p++] = i;
            for (i = 0; i < n; i++)
                if (sa[i] >= k) y[p++] = sa[i] - k;
            for (i = 0; i < m; i++) c[i] = 0;
            for (i = 0; i < n; i++) c[x[y[i]]]++;
            for (i = 0; i < m; i++) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for (i = 1; i < n; i++) x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
            if (p >= n) break;
            m = p;
        }
    }

    void build_height() {
        int i, k = 0;
        for (i = 0; i < n; i++) rank[sa[i]] = i;
        for (i = 0; i < n; i++) {
            if (k) k--;
            int j = sa[rank[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            height[rank[i]] = k;
        }
    }
}  // namespace SuffixArray

// 编号辅助
namespace SuffixArray {
    int idx[maxn];

    // 给字符串加上一个字符，属于字符串i
    void add(int ch, int i) {
        idx[n] = i;
        s[n++] = ch;
    }
}  // namespace SuffixArray

// LCP 模板
namespace SuffixArray {
    using std::min;
    int dp[maxn][20];
    void initRMQ(int n) {
        for (int i = 1; i <= n; i++) dp[i][0] = height[i];
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++) dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        return;
    }

    void initRMQ() { initRMQ(n - 1); }

    int lcp(int a, int b) {
        int ra = rank[a], rb = rank[b];
        if (ra > rb) swap(ra, rb);
        int k = 0;
        while ((1 << (k + 1)) <= rb - ra) k++;
        return min(dp[ra + 1][k], dp[rb - (1 << k) + 1][k]);
    }
}  // namespace SuffixArray

// 调试信息
namespace SuffixArray {
    using std::printf;
    void debug() {
        printf("n:%d\n", n);

        printf("%8s", "");
        for (int i = 0; i < n; i++) {
            printf("%4d", i);
        }
        printf("\n");

        printf("%8s", "s:");
        for (int i = 0; i < n; i++) {
            printf("%4d", s[i]);
        }
        printf("\n");

        printf("%8s", "sa:");
        for (int i = 0; i < n; i++) {
            printf("%4d", sa[i]);
        }
        printf("\n");

        printf("%8s", "rank:");
        for (int i = 0; i < n; i++) {
            printf("%4d", rank[i]);
        }
        printf("\n");

        printf("%8s", "height:");
        for (int i = 0; i < n; i++) {
            printf("%4d", height[i]);
        }
        printf("\n");
    }
}  // namespace SuffixArray