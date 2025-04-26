#include <bits/stdc++.h>
#include <vector>

using namespace std;

class countSubarrays2444 {
public:
    /*
    题目：统计定界子数组的数目
    给定一个整数数组 nums 和两个整数 minK 和 maxK，统计满足以下条件的子数组数目：
    1. 子数组的最小值等于 minK
    2. 子数组的最大值等于 maxK
    
    解题思路：
    1. 使用滑动窗口的思想，维护三个指针：
       - left：记录不满足条件的边界位置
       - minK_pos：记录最近一次出现 minK 的位置
       - maxK_pos：记录最近一次出现 maxK 的位置
    
    2. 遍历数组时：
       - 如果当前元素超出 [minK, maxK] 范围，更新 left
       - 如果当前元素等于 minK，更新 minK_pos
       - 如果当前元素等于 maxK，更新 maxK_pos
       - 计算以当前位置为右端点的有效子数组数目
    
    3. 有效子数组的判定：
       - 需要同时包含 minK 和 maxK
       - 子数组不能包含超出 [minK, maxK] 范围的元素
       - 子数组的起始位置必须在 left 之后
    
    时间复杂度：O(n)
    空间复杂度：O(1)
    */

    using ll = long long;
    ll countSubarrays(vector<int>& nums,int minK,int maxK){
        
        int left = -1,minK_pos = -1,maxK_pos = -1;
        ll ans = 0;
        for (int i = 0;i < static_cast<int>(nums.size());i++){
            if (nums[i] < minK || nums[i] > maxK){
                left = i;
            }
            if (nums[i] == minK) {
                minK_pos = i;
            }
            if(nums[i] == maxK){
                maxK_pos = i;
            }
            int valid_start = min(minK_pos,maxK_pos);
            if (valid_start > left) {
                ans += valid_start - left;
            }
        }
        return ans;
    }
    
};

int main(){
    countSubarrays2444 sol;
    vector<int> nums = {1,3,5,2,7,5};
    int minK = 1,maxK = 5;
    cout << sol.countSubarrays(nums,minK,maxK);
}