#include <iostream>
#include <vector>
using namespace std;
class move_zeroes283 {
public:
    void moveZeroes(vector<int>& nums) {
        auto n = nums.size();
        if(n == 1) return;
        auto non_zero_pos = 0;
        for(int i = 0; i < nums.size();++i) {
            if(nums[i] != 0) {
                nums[non_zero_pos++] = nums[i];
            }else {
                continue;
            }
        }
        for(;non_zero_pos < n;++non_zero_pos) {
            nums[non_zero_pos] = 0;
        }
    }
};

int main() {

    return 0;
}
