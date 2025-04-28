using namespace std;
#include <vector>
#include <iostream>
class twoSum2Solution{
public:
    vector<int> twoSum2(vector<int>& nums,int target){
        int n = nums.size();
        int left = 0,right = n - 1;
        while(left < right){
            int ans = nums[left] + nums[right];
            if(ans == target){
                return{left,right};
            }else if(ans > target){
                --right;
            }else{
                ++left;
            }
        }
        return {};
    }
};
int main() {
    twoSum2Solution ps;
    int target = 9;
    vector<int> nums = {2,7,11,15};
    auto res = ps.twoSum2(nums,target);

    return 0;
}
