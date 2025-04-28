#include <vector>
#include <iostream>
using namespace std;
class findMinSolution {
public:
    //arrays 严格递增
    static int findMin(vector<int>& nums) {
        int n = nums.size();
        int left = 0,right = n - 1;
        while(left < right) {
            int mid =(left + right) / 2;
            //拿中间的元素和最后一个元素比较 如果大于最后一个元素 那么证明旋转次数 大于 n / 2次 否则相反
            if(nums[mid] > nums[n - 1]) {
                left = mid + 1;
            }else {
                right = mid;
            }
        }
        return nums[left];
    }
};

int main() {
    findMinSolution ps;
    std::vector<int> nums = {2,3,4,5,1};
    std::cout << ps.findMin(nums) << std::endl;
    return 0;
}
//note: 最后一个值 要么是最小值 要么就是在最小值的右侧(即最小值在最后一个值左边。