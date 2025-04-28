//
// Created by 24276 on 2025/4/2.
//

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class find_anagrams438 {
public:
    vector<int> findAnagrams(string s,string p) {
        auto n = s.size();
        vector<int> ans;
        if(n < p.size()) return ans;    //若是s的长度比p还小 直接返回 无结果
        vector<int> pSymbolCount(26,0);   //使用数组代替哈希表 提高性能
        // unordered_map<char,int> mp;
        for(char c : p) {
            pSymbolCount[c - 'a']++;
        }
        vector<int> windowCount(26,0);
        int left  = 0,right = 0;
        while(right < n) {
            if(pSymbolCount[s[right] - 'a'] == 0) {
                windowCount = vector<int>(26,0);
                left = right + 1;
                right = left;
                continue;
            }
            windowCount[s[right] - 'a']++;
            while (windowCount[s[right] - 'a'] > pSymbolCount[s[right] - 'a']) {
                windowCount[s[right] - 'a']--;
                left++;
            }
            if (right - left + 1 == p.size()) {
                ans.push_back(left);
                windowCount[s[left] - 'a']--;
                left++;
            }
            right++;
        }
        return ans;
    }
};

int main() {
    find_anagrams438 solution;
    string s = "cbaebabacd",p = "abc";
    auto res = solution.findAnagrams(s,p);
    for(auto subscript : res) {
       cout <<  subscript << " ";
    }
    return 0;
}
