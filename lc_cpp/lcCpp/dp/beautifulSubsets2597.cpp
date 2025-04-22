#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;
class beautiful_subsets2597 {
public:
    int count;
    int beautifulSubsets(vector<int>& nums,int k) {
        unordered_set<int> current_set;
        int ans = count;
        backTrack(0,nums,k,current_set);
        return ans;
    }
    void backTrack(int index,vector<int>& nums,int k,unordered_set<int>& set) {
        if(index == nums.size()) {
            if(!set.empty()){
                ++count;
            }
            return;
        }
        // 不选当前
        backTrack(index + 1,nums,k,set);
        auto num = nums[index];
        if(set.find(num + k) == set.end() && set.find(num - k) == set.end()) {
            set.insert(num);
            backTrack(index + 1,nums,k,set);
            set.erase(num);
        }
    }
};
int main() {
    beautiful_subsets2597 ps;
    std::vector<int> nums = {2,4,6};
    cout << ps.beautifulSubsets(nums,2) << endl;
    return 0;
}
