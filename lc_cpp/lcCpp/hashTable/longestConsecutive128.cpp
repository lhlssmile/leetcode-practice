#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;
class longest_consecutive128{
public:
    /**
         * 用set 去重 因为有相同的nums[i]
         * 遍历set 对每个num 若是num - 1不在set中那么就创建一个新的key
         * 一直找num + 1,2,3.... 若都存在 记长度
         *
         *
         * 🌸这个问题本质上是找到一组连续整数的最长长度，类似于找最大子数组，
         * 但这里是连续整数而非数组索引连续。直接排序后遍历会超出时间复杂度要求（O(n log n)），因此需要线性时间解法。
         */
    int longestConsecutive(vector<int>& nums) {
        auto n = nums.size();
        //sort复杂度已经超过）O(n)
        pmr::unordered_set<int> numSet(nums.begin(),nums.end());
        int ans = 0;
        for(auto num : numSet) {
            if(numSet.find(num - 1) == numSet.end()) {
                //create new key?
                int current_num = num;
                int current_length = 0;
                while(numSet.find(current_num) != numSet.end()) {
                    ++current_length;
                    current_num++;
                }
                ans = std::max(ans,current_length);
            }
        }
         return ans;
    }
    int longestConsecutive2(vector<int>& nums) {
        int ans = 0;
        unordered_set<int> st(nums.begin(),nums.end());
        for(auto x : st) {
            if(st.find(x - 1) != st.end()) {
                continue;
            }
            int y = x + 1;
            while(st.find(y) != st.end()) {
                ++y;
            }
            ans = std::max(ans,y - x);
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {1,0,1,2};
    longest_consecutive128 ps;
    cout << ps.longestConsecutive2(nums) << endl;
    return 0;
}
