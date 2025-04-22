//
// Created by 24276 on 2025/4/12.
//

#include <vector>
#include <iostream>
using namespace std;
class min_operations100648 {
public:
    int minOperations(vector<int>& nums,int k ) {
        int sum = 0;
        for (int x : nums) {
            sum += x;
        }
        return sum % k;
    }
};

int main() {
    min_operations100648 sol;
    vector<int> nums = {3,2}; int k = 6;
    cout << sol.minOperations(nums,k);
    return 0;
}
