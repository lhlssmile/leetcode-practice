#include <numeric>
//
// Created by 24276 on 2025/8/12.
//
#include <string>
#include <vector>
using namespace std;
class maximum {
public:
    int maximumCostSubstring(string s, string chars, vector<int>& vals) {
        int mapping[26]{};
        std::iota(mapping, mapping + 26, 1);
        for (int i = 0; i < chars.length(); i++) {
            mapping[chars[i] - 'a'] = vals[i];
        }

        // 最大子数组和（允许子数组为空）
        int ans = 0, f = 0;
        for (char c : s) {
            f = max(f, 0) + mapping[c - 'a'];
            ans = max(ans, f);
        }
        return ans;
    }
};
