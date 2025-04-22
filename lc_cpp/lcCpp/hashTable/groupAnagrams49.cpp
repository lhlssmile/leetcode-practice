#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;
class group_anagrams49 {
public:

    vector<vector<string>> groupAnagramsMine(vector<string>& strs) {
        //这种实现是找子集的，这里这道题目要求出现次数也相同，不能用位掩码
        unordered_map<int, vector<string>> map; // 用 int 作为 key，32 位够用
        for (const string& s : strs) {
            int key = 0; // bitmask，26 位表示 a-z 是否出现
            for (char c : s) {
                key |= (1 << (c - 'a')); // 设置对应位为 1
            }
            map[key].push_back(s); // 放入对应分组
        }

        // 收集结果
        vector<vector<string>> res;
        for (auto& pair : map) {
            res.push_back(pair.second);
        }
        return res;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        /**
         *  共有strs.size()个字符串 record as n
         *  其中的每个字符 str 记长度为m
         *  排序每一个str 复杂度为 logm
         *  共nmlogm     空间复杂度为nm
         */
        pmr::unordered_map<string,vector<string>> map;
        for(auto str : strs) {
            auto sorted_s = str;
            std::sort(sorted_s.begin(),sorted_s.end());
            //ex:sorted 作为key(小到大  value是原来的str
            map[sorted_s].push_back(str);
        }
        vector<vector<string>> res;
        res.reserve(map.size());
        for(auto& [_,value] : map) {
            res.push_back(value);
        }
        return res;
    }
};

int main() {
    group_anagrams49 sol;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto res = sol.groupAnagrams(strs);
    cout << "[";
    for (size_t i = 0; i < res.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < res[i].size(); j++) {
            cout << "\"" << res[i][j] << "\"";
            if (j < res[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < res.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    return 0;
}
