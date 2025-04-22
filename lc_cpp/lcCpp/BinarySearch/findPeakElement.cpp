#include <vector>
#include <iostream>
using namespace std;
class findPeakElementSolution {
public:
    static int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int left = -1,right = n - 1;
        while(left + 1 < right) {
            int mid = left + (right - left ) / 2;
            if(nums[mid] > nums[mid + 1]) {
                right = mid;
            }else {
                left = mid;
            }
        }
        return right;
    }
};

int main() {
    findPeakElementSolution ps;
    std::vector<int> nums = {1,2,1,3,5,6,4};
    std::cout << ps.findPeakElement(nums) << std::endl;
    return 0;
}

