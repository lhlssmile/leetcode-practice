#include <iostream>
#include<vector>
using namespace std;
class rob_home_iilcr213 {
public:
    static int rob(vector<int>& nums) {
        const auto n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        if(n == 2) return std::max(nums[0],nums[1]);
        vector<int> dp(n);
        //分成两种情况 偷nums[0] 或者是 不偷
        //左闭区间 右开区间
        return max(nums[0]+rob1(nums,2,n-1),
            rob1(nums,1,n));
    }
    static int rob1(vector<int>& nums,int start, int end) {  // [start,end) 左闭右开
        int f0 = 0,f1 = 0;
        for(int i = start;i < end; ++i) {
            int new_f = max(f1,f0 + nums[i]);
            f0 = f1;
            f1 = new_f;
        }
        return f1;
    }
};

int main() {
    rob_home_iilcr213 ps;
    std::vector<int> nums = {2,3,2};
    const auto money = ps.rob(nums);
    cout << money << endl;
    return 0;
}


// /**
// *如果偷 nums[0]，那么 nums[1] 和 nums[n−1] 不能偷，问题变成从 nums[2] 到 nums[n−2] 的非环形版本，
// *调用 198 题的代码解决；
// 如果不偷 nums[0]，那么问题变成从 nums[1] 到 nums[n−1] 的非环形版本，同样调用 198 题的代码解决。
//
