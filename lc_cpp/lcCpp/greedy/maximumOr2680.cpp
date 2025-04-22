#include <iostream>
#include <vector>
using namespace std;

class maximumOr2680 {
public:
    long long maximumOr(vector<int>& nums,int k){
        int n = nums.size();
    vector<long long> prefix_or(n+1, 0);
    vector<long long> suffix_or(n+1, 0);
    
    // 计算前缀或
    for (int i = 0; i < n; ++i) {
        prefix_or[i+1] = prefix_or[i] | nums[i];
    }
    
    // 计算后缀或
    for (int i = n-1; i >= 0; --i) {
        suffix_or[i] = suffix_or[i+1] | nums[i];
    }
    
    long long max_or = 0;
    // 尝试对每个元素执行k次左移操作
    for (int i = 0; i < n; ++i) {
        long long current_or = prefix_or[i] | ((long long)nums[i] << k) | suffix_or[i+1];
        max_or = max(max_or, current_or);
    }
    
    return max_or;
    }
};
int main()
{
    maximumOr2680 ps;
    vector<int> nums = {12,9};
    int k = 1;
    cout << ps.maximumOr(nums,k) << endl;
    return 0;
}
