#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;
class three_sum15 {
public:
    //先选一个数 然后当成two Sum
    /**
     *
     * @param nums
     * @return
     * step1:先排序数组 使用双指针 并且跳过重复值
     * step2:遍历数组 固定第一个数nums[i] 如果与之前相同则跳过
     * step3:双指针找剩余数 left = i + 1 right 从末尾开始
     */
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        auto n = nums.size();
        for(int i = 0; i < nums.size() - 2; ++i) {
            if(i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1,right = n -1;
            while(left < right) {
                auto sum = nums[i] + nums[left] + nums[right];
                if(sum == 0) {
                    res.push_back({nums[i],nums[left],nums[right]});
                    while(left < right && nums[left] == nums[left + 1]) left++;
                    while(left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                }else if(sum < 0) {
                    ++left;
                }else {
                    --right;
                }
            }
        }
        return res;
    }
};

int main() {
    three_sum15 ps;
    vector<int> nums = {-1,0,1,2,-1,4};
    auto res = ps.threeSum(nums);
    cout << "[" << " ";
    for(auto const vec : res) {
        cout << "[" << " ";
        for(auto const ele : vec) {
            cout << ele << " ";
        }
        cout << "]" << " ";
    }
    cout << "]" << endl;
    return 0;
}

