#include <vector>

using namespace std;
class count_max_or_subsets {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int ans = 0;
        int total_or = reduce(nums.begin(), nums.end(), 0, bit_or());
        auto dfs = [&](this auto&& dfs, int i, int curr) -> void {
            if (i == nums.size()){
                if (curr == ans) {
                    ans++;
                }
                return ;
            }
            dfs(i + 1, curr);
            dfs(i + 1, curr | nums[i]);
        };

        dfs(0, 0);
        return ans;
    }
};

int main(){
    count_max_or_subsets solution;
    vector<int> nums = {3, 1};
    auto ans = solution.countMaxOrSubsets(nums);
    return 0;
}