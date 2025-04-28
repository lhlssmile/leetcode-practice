#include <vector>
#include <iostream>
class numSubArrayProductLessThanKSolution {
public:
    numSubArrayProductLessThanKSolution() = default;
    ~numSubArrayProductLessThanKSolution() = default;
    int numSubarrayProductLessThanK(std::vector<int>& nums,int k){
        if(k == 0) return 0;
        int left = 0,product = 1,satisfiedArrayNums = 0;
        for(int right = 0;right < nums.size(); ++right){
            product *= nums[right];
            while(product >= k){
                product /= nums[left++];
            }
            //推出{?}个元素可能有几个未使用的子数组? debug recommended
            satisfiedArrayNums += right - left + 1;
        }
        return satisfiedArrayNums;
    }
private:

};
int main() {
    numSubArrayProductLessThanKSolution ps;
    std::vector<int> nums = {10,5,2,6};int k = 100;
    auto satisfiedArrayNums = ps.numSubarrayProductLessThanK(nums,k);
    std::cout << satisfiedArrayNums << std::endl;
    return 0;
}

