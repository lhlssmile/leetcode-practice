#include <iostream>
#include <unordered_map>
#include <vector>

class beautiful_subarrays2588 {
public:
    long long beautifulSubarrays(std::vector<int>& nums) {
        //key做前缀 value是出现次数 如果一个前缀在此出现 那么之间的子数组必定为美丽子数组
        long long result = 0;
        auto n = nums.size();
        std::unordered_map<int,int> prefixXOR;
        //空数组的异或为1
        prefixXOR[0] = 1;
        int currentXOR = 0;
        for(int i = 0;i < nums.size();++i) {
            currentXOR ^= nums[i];
            result += prefixXOR[currentXOR];
            prefixXOR[currentXOR]++;
        }
        return result;
    }
    long long beautifulSubArrays(std::vector<int>& nums) {
        long long result = 0;
        //key as prefixSUM, value as appearTimes
        std::unordered_map<int,int> prefixXOR;
        prefixXOR[0] = 1;
        auto n = nums.size();
        auto current_XOR = 0;
        for(int i = 0;i < n;++i) {
            current_XOR ^= nums[i];
            result += prefixXOR[current_XOR];
            prefixXOR[current_XOR]++;
        }
        return result;
    }
};

int main() {
    beautiful_subarrays2588 ps;
    std::vector<int> nums = {4,3,1,2,4};
    std::cout << ps.beautifulSubarrays(nums) << std::endl;
    return 0;
}
