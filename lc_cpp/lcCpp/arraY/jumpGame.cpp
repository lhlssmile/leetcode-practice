#include <iostream>
#include <vector>
#include <climits>

class jumpGameSolution{
public:
    int jump(std::vector<int>& nums){
        auto n = nums.size();
        if(n <= 1) return 0;
        int jump_times = 0;     //jump times
        int current_end = 0;    //current scope
        int farthest = 0;       //farthest position in current scope
        for (int i = 0; i < static_cast<int>(n - 1); ++i) {
            farthest = std::max(farthest,i + nums[i]);
            if (i == current_end){
                ++jump_times,current_end = farthest;
                if (current_end >= static_cast<int>(n - 1)) break;
            }
        }
        return jump_times;
    }
};
int main() {
    jumpGameSolution ps;std::vector<int> nums = {2,3,1,1,4};
    std::cout << ps.jump(nums) << std::endl;
    return 0;
}
