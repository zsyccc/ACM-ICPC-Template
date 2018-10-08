#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

// 字符串分割，分隔符为字符，可为多字符，前后不留空字符串
// *a,b*c,d, 按,*分割 -> {"a","b","c","d"}
// 注意：源字符串s将会被改变，请勿使用string.c_str()
// s源字符串 t传出结果 sep分隔符字符串(分隔符为每个单字符)
void split(char *s, vector<string> &v,const char *sep) {
    char *p = strtok(s, sep);
    while (p) {
        v.push_back(string(p));
        p = strtok(NULL, sep);
    }
}

int main() {
    char s[] = "cabcacac";
    vector<string> v;
    split(s, v, "c");
    for (auto k : v) {
        cout << k << endl;
    }
    cout << v.size() << endl;
    return 0;
}
