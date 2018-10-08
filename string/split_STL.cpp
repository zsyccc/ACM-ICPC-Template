#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 字符串分割，分隔符为字符串，前后留空字符串
// cabcacac 按c分割 -> {"","ab","a","a",""}
// s源字符串 v传出结果 c分隔符字符串
void split(const std::string& s, std::vector<std::string>& v,
                 const std::string& c) {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 <= s.length()) v.push_back(s.substr(pos1));
    // if (pos1 != s.length()) v.push_back(s.substr(pos1));
    // 去除最后空串
}
