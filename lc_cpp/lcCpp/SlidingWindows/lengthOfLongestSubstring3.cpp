#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
class lengthOfLongestSubStringSolution {
public:
    lengthOfLongestSubStringSolution() = default;
    ~lengthOfLongestSubStringSolution() = default;
    int lengthOfLongestSubstring(std::string s){
        std::unordered_map<char,int> mp;
        int ans = 0;
        if(s.size() == 0) return 0;
        int left = 0, n = s.size();
        for(int right = 0; right < n; ++right){
            char c = s[right];
            mp[c]++;
            while(mp[c] > 1){
                mp[s[left++]]--;
            }
            ans = max(ans,right - left + 1);
        }
        return ans;
    }
private:

};
int main() {
    lengthOfLongestSubStringSolution ps;
    std::cout << ps.lengthOfLongestSubstring("abcabcbb") << std::endl;
    return 0;
}

