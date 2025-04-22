#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class find_matrix2610 {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        //use map record element appear times
        std::unordered_map<int, int> freq;
        int maxFreq = 0;
        for (int num : nums) {
            freq[num]++;
            maxFreq = std::max(maxFreq, freq[num]);
        }

        // 行数等于最大频率
        std::vector<std::vector<int>> result(maxFreq);
        for (auto& [num, count] : freq) {
            for (int i = 0; i < count; i++) {
                result[i].push_back(num);
            }
        }

        return result;
    }
};

int main() {
    find_matrix2610 ps;
    vector<int> nums = {1,3,4,1,2,3,1};
    auto res = ps.findMatrix(nums);
    for(auto const vec : res) {
        std::cout << "[" ;
        for(auto const ele : vec) {
            cout << ele << " ";
        }
        std::cout << "]";
    }
    return 0;
}
