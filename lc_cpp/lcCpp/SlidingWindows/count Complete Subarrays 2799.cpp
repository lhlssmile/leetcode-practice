#include <bits/stdc++.h>
#include <vector>
using namespace std;
class countCompleteSubarrays2799 {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        unordered_set<int> st(nums.begin(), nums.end());
        int n = nums.size(),left = 0,right = 0,ans = 0;
        unordered_map<int,int> freq;
        // @brief 关键在于以某个位置为右端点，向左扩展有多少合法的子数组
        for(;right < n;right++){
            freq[nums[right]]++;
            while(freq.size() == st.size()){
                ans += n - right;
                freq[nums[left]]--;
                if(freq[nums[left]] == 0){
                    freq.erase(nums[left]);
                }
                ++left;
            }

        }
        return ans;
    }
};
int main(){
    vector<int> nums = {1,3,1,2,2};
    countCompleteSubarrays2799 sol;
    cout << sol.countCompleteSubarrays(nums);
    return 0;
}