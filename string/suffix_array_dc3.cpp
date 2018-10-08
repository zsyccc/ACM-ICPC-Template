#include <cstdio>

using namespace std;

/*
注意：
1.maxn开n的十倍大小;
2.dc3(r,sa,n+1,Max+1);r为待后缀处理的数组,sa为存储排名位置的数组,n+1和Max+1都和倍增一样
3.calheight(r,sa,n);和倍增一样
*/
// DC3 算法
namespace SuffixArray {
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x)*3 + 1 : ((x)-tb) * 3 + 2)
    using std::printf;
    
    const int maxn = 1e7 + 5;

    int wa[maxn], wb[maxn], wv[maxn], ws[maxn];
    int s[maxn], sa[maxn];
    int rank[maxn], height[maxn];
    int n;

    int c0(int *r, int a, int b) {
        return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
    }

    int c12(int k, int *r, int a, int b) {
        if (k == 2)
            return r[a] < r[b] || (r[a] == r[b] && c12(1, r, a + 1, b + 1));
        else
            return r[a] < r[b] || (r[a] == r[b] && wv[a + 1] < wv[b + 1]);
    }

    void sort(int *r, int *a, int *b, int n, int m) {
        int i;
        for (i = 0; i < n; i++) wv[i] = r[a[i]];
        for (i = 0; i < m; i++) ws[i] = 0;
        for (i = 0; i < n; i++) ws[wv[i]]++;
        for (i = 1; i < m; i++) ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--) b[--ws[wv[i]]] = a[i];
        return;
    }

    void dc3(int *r, int *sa, int n, int m) {
        int i, j, *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0,
                  p;
        r[n] = r[n + 1] = 0;
        for (i = 0; i < n; i++)
            if (i % 3 != 0) wa[tbc++] = i;
        sort(r + 2, wa, wb, tbc, m);
        sort(r + 1, wb, wa, tbc, m);
        sort(r, wa, wb, tbc, m);
        for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++)
            rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
        if (p < tbc)
            dc3(rn, san, tbc, p);
        else
            for (i = 0; i < tbc; i++) san[rn[i]] = i;
        for (i = 0; i < tbc; i++)
            if (san[i] < tb) wb[ta++] = san[i] * 3;
        if (n % 3 == 1) wb[ta++] = n - 1;
        sort(r, wb, wa, ta, m);
        for (i = 0; i < tbc; i++) wv[wb[i] = G(san[i])] = i;
        for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++)
            sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
        for (; i < ta; p++) sa[p] = wa[i++];
        for (; j < tbc; p++) sa[p] = wb[j++];
        return;
    }

    void build_height(int n) {
        int i, j, k = 0;
        for (i = 1; i <= n; i++) rank[sa[i]] = i;
        for (i = 0; i < n; height[rank[i++]] = k)
            for (k ? k-- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
                ;
        return;
    }

    void build_height() { build_height(n - 1); }

    void build_sa(int m) { dc3(s, sa, n, m); }

    // LCP 模板
    int RMQ[maxn];
    int mm[maxn];
    int best[20][maxn];

    void initRMQ(int n) {
        int i, j, a, b;
        for (mm[0] = -1, i = 1; i <= n; i++)
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
        for (i = 1; i <= n; i++) best[0][i] = i;
        for (i = 1; i <= mm[n]; i++)
            for (j = 1; j <= n + 1 - (1 << i); j++) {
                a = best[i - 1][j];
                b = best[i - 1][j + (1 << (i - 1))];
                if (RMQ[a] < RMQ[b])
                    best[i][j] = a;
                else
                    best[i][j] = b;
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

        printf("%8s", "height:");
        for (int i = 0; i < n; i++) {
            printf("%4d", height[i]);
        }
        printf("\n");
    }
}  // namespace SuffixArray
