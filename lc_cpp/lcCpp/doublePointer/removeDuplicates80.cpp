#include <iostream>
#include <vector>
using namespace std;
class remove_duplicates80 {
public:
    static int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 1 || nums.size() == 2) return nums.size();
            // nums have sorted
        int n = nums.size();
        int slow = 2;
         for(int fast = 2;fast < n;++fast) {
            if(nums[fast] != nums[slow - 2]) {
                nums[slow] = nums[fast];
                ++slow;
            }
        }
        return slow;
    }
};

int main() {
    remove_duplicates80 ps;
    std::vector<int> nums = {0,0,1,1,1,1,2,3,3};
    auto len = ps.removeDuplicates(nums);
    std::cout << len << std::endl;
    return 0;
}
