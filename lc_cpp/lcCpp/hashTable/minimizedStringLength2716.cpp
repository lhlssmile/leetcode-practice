//
// Created by 24276 on 2025/3/28.
//
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;
class minimized_string_length2716 {
public:
    int minimizedStringLength(string s) {
        unordered_map<char,int> mp;
        auto minized_length = 0;
        auto n = s.size();
        for (char c : s) {
            mp[c]++;
        }
        return minized_length = mp.size();
    }
    int minimizedStringLengthA(string s) {
        unsigned mask = 0;
        for(char c : s) {
            mask |= 1 << (c - 'a');
        }
        //population count -> 数1的个数
        return popcount(mask);
    }
};

int main() {
    minimized_string_length2716 solution;
    string s = "dddaaa";
    cout << solution.minimizedStringLengthA(s) << endl;
    return 0;
}
