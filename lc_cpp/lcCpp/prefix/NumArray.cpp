//
// Created by 24276 on 2025/8/8.
//
#include <vector>
class num_array {
    std::vector<int> s;
public:
    num_array(std::vector<int>& nums) {
        s.resize(nums.size() + 1);
        for (int i = 0; i < nums.size(); i++) {
            s[i + 1] = s[i] + nums[i];
        }
    }
    int sumRange(int left, int right ) {
        return s[right + 1] - s[left];
    }
};

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    num_array ps(nums);
    int res = ps.sumRange(2, 4);
    return 0;
}
