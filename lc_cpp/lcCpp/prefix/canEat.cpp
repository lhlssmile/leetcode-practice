//
// Created by 24276 on 2025/8/8.
//
#include <vector>
using namespace std;
class can_eat {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        // q[0]: favorite type, q[1]: favorite day, q[2]: dailyCap(MAX EATING COUNTS)
        int n = candiesCount.size();
        vector<int> prefix (n + 1, 1);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + candiesCount[i];
        }
        vector<bool> ans(queries.size(), false);
        int idx = 0;
        for (auto& q : queries) {
            int candy_type = q[0], favorite_day = q[1], daily_capacity = q[2];

            long long min_candy = (long long)favorite_day + 1;
            long long max_candy = (long long)daily_capacity * min_candy;

            long long candy_start = prefix[candy_type] + 1;
            long long candy_end = prefix[candy_type + 1];

            ans[idx++] = !(max_candy < candy_start || min_candy > candy_end);
        }
        return ans;
    }
};

int main() {
    can_eat ps;
    vector<int> candiesCount = {7, 4, 5, 3, 8};
    vector<vector<int>> queries = {{0, 2, 2}, {4, 2, 4}, {2, 13, 1000000000}};
    vector<bool> ans = ps.canEat(candiesCount, queries);
    return 0;
}
