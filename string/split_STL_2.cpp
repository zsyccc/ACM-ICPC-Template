#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 字符串分割，分隔符为字符，可为多字符，前后不留空字符串
// **a,b*c,d, 按,*分割 -> {"a","b","c","d"}
// strtok 的 实现
// s源字符串 t传出结果 sep分隔符字符串(分隔符为每个单字符)
void split(const string &s, vector<string> &v, const string &sep) {
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        //找到字符串中首个不等于分隔符的字母；
        int flag = 0;
        while (i != s.size() && flag == 0) {
            flag = 1;
            for (string_size x = 0; x < sep.size(); ++x) {
                if (s[i] == sep[x]) {
                    ++i;
                    flag = 0;
                    break;
                }
            }
        }

        //找到又一个分隔符，将两个分隔符之间的字符串取出；
        flag = 0;
        string_size j = i;
        while (j != s.size() && flag == 0) {
            for (string_size x = 0; x < sep.size(); ++x) {
                if (s[j] == sep[x]) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) ++j;
        }
        if (i != j) {
            v.push_back(s.substr(i, j - i));
            i = j;
        }
    }
}

int main() {
    string s = "cabcacac";
    vector<string> v;
    split(s, v, "c");
    for (auto k : v) {
        cout << k << endl;
    }
    cout << v.size() << endl;
    return 0;
}
