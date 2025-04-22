//
// Created by 24276 on 2025/3/30.
//


#include <string>
#include <iostream>
#include <vector>
using namespace std;

class add_spaces2109 {
public:
    string addSpaces(string s,vector<int>& spaces) {
        //silly
        auto n = spaces.size();
        for(int i = 1;i <= n; i++) {
            //这是直接替换了 不是加空格
            string suffix_str = s.substr(spaces[i - 1] +(i - 1),s.size() - spaces[i - 1] - (i - 1));
            s[spaces[i - 1] + i - 1] = ' ';
            string prefix_str = s.substr(0,spaces[i - 1] + i);
            s = prefix_str + suffix_str;
        }
        return s;
    }
    string addSpaceas(string s, vector<int>& spaces) {
        int n = s.size(), k = spaces.size();
        string result(n + k, 0);  // 创建一个新字符串，长度为原字符串长度加空格数

        int j = 0;  // result的索引
        int spaceIdx = 0;  // spaces的索引

        for (int i = 0; i < n; i++) {
            // 如果当前位置需要添加空格
            if (spaceIdx < k && i == spaces[spaceIdx]) {
                result[j++] = ' ';
                spaceIdx++;
            }
            result[j++] = s[i];
        }

        return result;
    }
    string addSpacesa(string s, vector<int>& spaces) {
        int n = s.size();
        int k = spaces.size();

        // 扩展字符串长度以容纳空格
        s.resize(n + k);

        // 从右向左填充
        int oldIndex = n - 1;      // 原字符串的读取位置
        int newIndex = n + k - 1;  // 新字符串的写入位置
        int spaceIndex = k - 1;    // spaces数组的索引(从右到左)

        while (oldIndex >= 0) {
            // 先复制原字符
            s[newIndex--] = s[oldIndex];

            // 检查是否需要在当前位置之前插入空格
            if (spaceIndex >= 0 && oldIndex == spaces[spaceIndex]) {
                s[newIndex--] = ' ';
                spaceIndex--;
            }

            oldIndex--;
        }

        return s;
    }
};

int main() {
    add_spaces2109 solution;
    string s = "LeetcodeHelpsMeLearn";
    vector<int> spaces = {8,13,15};
    cout << solution.addSpacesa(s,spaces) << endl;
    return 0;
}
