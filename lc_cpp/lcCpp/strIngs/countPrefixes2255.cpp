#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class count_prefixes2255 {
public:
    int countPrefixes(vector<string>& words,string s) {
        int ans = 0;
        for(auto const& str : words) {
            if(str.size() > s.size()) {
                continue;
            }
            bool isPrefix = true;
            for(int i = 0;i < str.size();++i) {
                // 连续子字符串
                if (s[i] - str[i] != 0) {
                    isPrefix = false;
                    break;
                }
            }
            if (isPrefix) {
                ++ans;
            }
        }
        return ans;
    }
    int countPrefixed(vector<string>& words,string s) {
        return ranges::count_if(words,[&](auto& word) {
            return s.starts_with(word);
        });
    }
};

int main() {
    count_prefixes2255 solution;
    vector<string> words = {"a","b","c","ab","bc","abc"};
    string s = "abc";
    std::cout << solution.countPrefixed(words,s) << std::endl;
    return 0;
}
