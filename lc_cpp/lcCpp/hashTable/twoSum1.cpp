#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;
class two_sum1 {
public:

    vector<int> twoSum(vector<int>& nums,int target) {
        //key is value ,value is subScript;
        unordered_map<int,int> map;
        for(int i = 0; i < nums.size(); ++i) {
            auto curr = map.find(target - nums[i]);
            // auto pair = map.find(target);
            if(curr != map.end()) {
                return {curr->second,i};
            }
            map[nums[i]] = i;
        }
        return {};
    }
};

int main() {
    two_sum1 ps;
    vector<int> nums = {2,7,11,15};
    int target = 9;
    auto res = ps.twoSum(nums,target);
    for(auto const sub : res) {
        cout << sub << " ";
    }
    return 0;
}
