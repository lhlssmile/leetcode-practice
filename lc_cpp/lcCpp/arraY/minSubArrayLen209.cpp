#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class minSubArrayLengthSolution {
public:
    minSubArrayLengthSolution() = default;
    ~minSubArrayLengthSolution() = default;
    int minSubArrayLen(int target,vector<int>& nums){
        //滑动窗口
        /**
         * 滑动窗口的核心要点：
            1.维护一个有条件的滑动窗口；
            2.右端点右移，导致窗口扩大，是不满足条件的罪魁祸首；
            3.左端点右移目的是为了缩小窗口，重新满足条件
         */
        //returned sub array must continuous?
        int n = nums.size();
        int left = 0,sum = 0;
        int ans = INT_MAX;
        for(int right = 0; right < n; ++right){
            sum += nums[right];
            while(sum >= target){
                ans = min(ans,right - left + 1);
                sum -= nums[left++];
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
private:

};


int main() {
    minSubArrayLengthSolution ps;
    vector<int> nums = {2,3,1,2,4,3};int target = 7;
    int length = ps.minSubArrayLen(target,nums);
    cout << length << endl;
    return 0;
}
