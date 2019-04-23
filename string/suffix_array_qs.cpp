#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

namespace SuffixArray {
    using std::printf;

    const int maxn = 1e7 + 5;  // max(字符串长度，最大字符值加1)

    int s[maxn];  // 原始字符数组（最后一个字符应必须是0，而前面的字符必须非0）
    int sa[maxn];                      // 后缀数组
    int t[maxn], rank[maxn], c[maxn];  // 辅助数组
    int n;  // 字符个数（包括最后一个0字符）

    void clear() {
        n = 0;
        memset(sa, 0, sizeof(sa));
    }

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

    void build_sa(int xxxxx) {
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = i < n ? s[i] : -1;
        }
        for (k = 1; k < n; k <<= 1) {
            sort(sa, sa + n, compare_sa);
            t[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                t[sa[i]] =
                    t[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
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

    // LCP 模板
    const int* RMQ = height;
    int mm[maxn];
    int best[20][maxn];

    void initRMQ(int n) {
        int i, j, a, b;
        for (mm[0] = -1, i = 1; i <= n; i++)
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
        for (i = 1; i <= n; i++) best[0][i] = i;
        for (i = 1; i <= mm[n]; i++) {
            for (j = 1; j <= n + 1 - (1 << i); j++) {
                a = best[i - 1][j];
                b = best[i - 1][j + (1 << (i - 1))];
                if (RMQ[a] < RMQ[b])
                    best[i][j] = a;
                else
                    best[i][j] = b;
            }
        }
        return;
    }

    void initRMQ() { initRMQ(n - 1); }

    int askRMQ(int a, int b) {
        int t;
        t = mm[b - a + 1];
        b -= (1 << t) - 1;
        a = best[t][a];
        b = best[t][b];
        return RMQ[a] < RMQ[b] ? a : b;
    }

    int lcp(int a, int b) {
        int t;
        a = rank[a];
        b = rank[b];
        if (a > b) {
            t = a;
            a = b;
            b = t;
        }
        return (height[askRMQ(a + 1, b)]);
    }

    int idx[maxn];
    // 给字符串加上一个字符，属于字符串i
    void add(int ch, int i) {
        idx[n] = i;
        s[n++] = ch;
    }

    void init() { n = 0; }

    //输出信息
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

        // printf("%8s", "height:");
        // for (int i = 0; i < n; i++) {
        //     printf("%4d", height[i]);
        // }
        printf("\n");
    }
}  // namespace SuffixArray