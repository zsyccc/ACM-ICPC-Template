#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 字符串分割，分隔符为字符串，前后留空字符串
// cabcacac 按c分割 -> {"","ab","a","a",""}
// s源字符串 v传出结果 c分隔符字符串
void split(const string& s, vector<string>& v, const string& c) {
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 <= s.length()) v.push_back(s.substr(pos1));
    // 如果要去除最后空串,用下方语句替代上一条
    // if (pos1 != s.length()) v.push_back(s.substr(pos1));
}
