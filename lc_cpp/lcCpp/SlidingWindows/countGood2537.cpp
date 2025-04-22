//
// Created by 24276 on 2025/4/16.
//

#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class count_good2537 {
public:
    using ll = long long;
    ll countGood(vector<int>& nums,int k) {
        int n = nums.size();
        long long ans = 0;
        long long pair_count = 0;
        unordered_map<int, int> freq;
        int left = 0;

        for (int right = 0; right < n; right++) {
            int num = nums[right];
            pair_count += freq[num];
            freq[num]++;

            while (pair_count >= k && left <= right) {
                int left_num = nums[left];
                freq[left_num]--;
                pair_count -= freq[left_num];
                left++;
            }

            ans += left;
        }

        return ans;
    }
};

int main() {
    count_good2537 sol;
    vector<int> nums = {3,1,4,3,2,2,4}; int k = 2;
    cout << sol.countGood(nums,k);
    return 0;
}
