#include <cstring>
#include <vector>
using namespace std;

const int wordnum = 100;
const int wordlen = 4000;
const int maxnode = wordnum * wordlen + 10;
const int sigma_size = 26;

// 字母表为全体小写字母的Trie
struct Trie {
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz;  // 结点总数
    void clear() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }                                    // 初始时只有一个根结点
    int idx(char c) { return c - 'a'; }  // 字符c的编号

    // 插入字符串s，附加信息为v。注意v必须非0，因为0代表“本结点不是单词结点”
    void insert(const char *s, int v) {
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if (!ch[u][c]) {  // 结点不存在
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;      // 中间结点的附加信息为0
                ch[u][c] = sz++;  // 新建结点
            }
            u = ch[u][c];  // 往下走
        }
        val[u] = v;  // 字符串的最后一个字符的附加信息为v
    }
};
