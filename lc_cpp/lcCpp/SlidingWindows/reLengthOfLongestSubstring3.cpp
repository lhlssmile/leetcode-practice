#include <string>
#include <iostream>
using namespace std;
#include <unordered_map>
class reLengthOfLongestSubstring3{
public:
    int lengthOfLongestSubstrings(string s) {
        pmr::unordered_map<char,int> map;     //string:s[i] int:appear times
        auto n = s.size();
        if(n == 0) return 0;int ans = 0;
        int left = 0;
        for(int right = 0;right < n;++right) {
            auto c = s[right];
            map[c]++;
            while(map[c] > 1) {
                map[s[left]++]--;
            }
            ans = std::max(ans,right - left + 1);
        }
        return ans;
    }
};

int main() {
    reLengthOfLongestSubstring3 ps;
    cout << ps.lengthOfLongestSubstrings("abcabcbb") << endl;
    return 0;
}
