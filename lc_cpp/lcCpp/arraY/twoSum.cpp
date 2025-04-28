#include <unordered_map>
#include <iostream>
#include <vector>
class twoSumSolution{
    public:
        std::vector<int> twoSum(std::vector<int>& nums, int target) {
            int n = nums.size();
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (nums[i] + nums[j] == target) {
                        return {i, j};
                    }
                }
            }
            return {};
        }

    std::vector<int> twoSumHash(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> hashtable;
    for (int i = 0; i < nums.size(); ++i) {
        auto it = hashtable.find(target - nums[i]);
        if (it != hashtable.end()) {
            return {it->second, i};
        }
        hashtable[nums[i]] = i;
    }
    return {};
}
};

int main() {
    twoSumSolution ps;
    std::vector<int> nums = {3,2,4};int target = 6;
    auto subscripts = ps.twoSumHash(nums,target);
    std::cout << "[" << std::endl;
    for(const auto& subScript : subscripts){
        std::cout << subScript << " ";
    }
    std::cout << "]" << std::endl;
    return 0;
}

