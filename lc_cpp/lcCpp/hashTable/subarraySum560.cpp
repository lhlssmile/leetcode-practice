#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
class subarray_sum560{
public:
    /**
     * 1.用前缀和作为key, value则是此前缀和出现的次数?
     * @param nums
     * @param k
     * @return
     */
    int subarraySum(vector<int>& nums,int k) {
        unordered_map<int,int> prefix_sum_count;
        int pre_sum = 0;
        int count = 0;
        prefix_sum_count[pre_sum] = 1;
        auto n = nums.size();
        for(int i = 0;i < n;++i) {
            pre_sum += nums[i];
            if(prefix_sum_count.find(pre_sum - k) != prefix_sum_count.end()) {
                count += prefix_sum_count[pre_sum - k];
            }
            prefix_sum_count[pre_sum]++;
        }
        return count;
    }
};
int main(){
    subarray_sum560 ps;
    vector<int> nums = {1,1,1};
    cout << ps.subarraySum(nums,2) << endl ;

    return 0;
}
