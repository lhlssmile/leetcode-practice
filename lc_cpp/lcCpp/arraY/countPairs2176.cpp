//
// Created by 24276 on 2025/4/17.
//

#include <vector>
#include <iostream>
#include <numeric>
#include <unordered_map>

using namespace std;

const int MX = 101;
vector<int> divisors[MX];

auto init = [] {
   for (int i = 1;i < MX;i++) {
       for (int j = i;j < MX;j+= i) {
           divisors[j].push_back(i);
       }
   }
    return 0;
}();
class count_pairs2176 {
public:
    /**
     * 先找到i,j的最大公约数
     * 一般地 枚举j 那么i必须是k` = k / GCD(k,j)的倍数   -> ex:k = 12,j = 9 那么i 只要为4的倍数(4,8,12...)就满足条件
     * @param nums
     * @param k
     * @return
     */
    int countPairs(vector<int>& nums,int k) {
        int n = nums.size();
        int ans = 0;
        unordered_map<int,int> cnt;
        for (int j = 0;j < n;j++) {
            int x = nums[j];
            if (j && x == nums[0]) {
                ans++;      //此时ij % k 一定为0
            }
            int k2 = k / std::gcd(k,j);
            ans += cnt[k2 << 10 | x];
            for (int d : divisors[j]) {
                cnt [d << 10 | x] ++;
            }
        }
        return ans;
    }
};

int main() {
    count_pairs2176 sol;
    vector<int> nums = {3,1,2,2,2,1,3};
    cout << sol.countPairs(nums,2);
    return 0;
}
