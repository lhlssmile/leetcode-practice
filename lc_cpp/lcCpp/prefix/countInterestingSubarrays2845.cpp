#include <bits/stdc++.h>
#include <vector>
using namespace std;

class countInterestingSubarrays2845 {
public:
    using ll = long long;
    ll countInterestingSubarrays(vector<int>& nums, int k, int modulo) {
        std::pmr::unordered_map<int,ll> count;
        ll ans = 0;int prefix_sum = 0;
        for(int num : nums){
            if(num % modulo == k){
                prefix_sum++;
            }
            int need = (prefix_sum - k) % modulo;
            if (need < 0) need += modulo;
            if(count.count(need)){
                ans += count[need];
            }
            count[prefix_sum % modulo]++;
            // @brief 这里的count[prefix_sum % modulo]++是在count[need]之后的，所以不需要考虑need == prefix_sum % modulo
        }
        return ans;
    }
};
int main(){
    vector<int> nums = {3,2,4};
    int k = 1,modulo = 2;
    countInterestingSubarrays2845 c;
    cout << c.countInterestingSubarrays(nums,k,modulo) << endl;
    return 0;
}