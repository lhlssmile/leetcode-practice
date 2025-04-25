//
// Created by 24276 on 2025/4/25.
//

#include <bits/stdc++.h>
#include <vector>

using namespace std;

class min_costs3502 {
public :
    vector<int> minCosts(vector<int>& cost) {
        int n = cost.size();
        vector<int> ans (n);
        ans[0] = cost[0];
        for (int i = 1;i < n;i++) {
            ans[i] = min(ans[i - 1],cost[i]);
        }
    return ans;
}
};

int main() {
    min_costs3502 sol;
    vector<int> cost = {5,3,4,1,3,2};
    auto res = sol.minCosts(cost);
    for (int ele : res) {
        cout << ele << " ";
    }
    return 0;
}
