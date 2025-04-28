#include <vector>
#include <unordered_set>
#include <iostream>
class longestConsecutiveSolution{
public:
    int longestConsecutive(std::vector<int>& nums){
        if (nums.empty()) return 0;
        std::unordered_set<int> num_set(nums.begin(),nums.end());
        int longest = 0;
        for(auto num : nums){
            if(num_set.find(num - 1) == num_set.end()){
                int current_num = num;
                int current_streak = 1;
                while (num_set.find(current_num + 1) != num_set.end()) {
                    current_num++;
                    current_streak++;
                }
                longest =  std::max(longest,current_streak);
            }
        }
        return longest;
    }
};
int main() {
    longestConsecutiveSolution ps;
    std::vector<int> nums = {0,3,7,2,5,8,4,6,0,1};
    std::cout << ps.longestConsecutive(nums) << std::endl;
    return 0;
}
