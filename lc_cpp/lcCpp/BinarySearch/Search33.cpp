#include <vector>
#include <iostream>
using namespace std;

class search33Solution {
public:
    static int search(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            }

            // 判断左半部分是否有序
            if (nums[left] <= nums[mid]) {
                // 如果目标值在左半部分的范围内
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else { // 否则右半部分有序
                // 如果目标值在右半部分的范围内
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};

int main() {
    search33Solution ps;
    std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    const int target = 0;
    std::cout << ps.search(nums, target) << std::endl; // 输出应该是 4
    return 0;
}