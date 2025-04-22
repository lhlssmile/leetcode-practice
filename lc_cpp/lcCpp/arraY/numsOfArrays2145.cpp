//
// Created by 24276 on 2025/4/21.
//

#include <vector>
#include <iostream>
using namespace std;
class nums_of_arrays2145 {
public:
    //ultra violence😭😭 timeout
    int numsOfArrays(vector<int>& differences,int lower,int upper) {
        int n = differences.size(),array_nums = 0;
        vector<int> hidden(n + 1,lower);        //直接确定hidden[0] = lower
        while(hidden[0] <= upper) {
        int i = 0;
            bool count = true;
        for(;i < n;i++) {
            hidden[i + 1] = differences[i] + hidden[i];
            if (hidden[i + 1] < lower || hidden[i + 1] > upper) {
                //每次不满足条件就要重新选第一个hidden[0]
                count = false;
                break;
                }
            }
            //是选出了一个还是 break出来了?
            if (count) {
                array_nums += 1;
            }
            hidden[0] += 1;
        }
        return array_nums;
}
    //prefix
    using ll = long long ;
    int numsOfArraysRE(vector<int>& differences,int lower,int upper) {
        int n = differences.size();
        ll prefix = 0;
        ll min_prefix  = 0,max_prefix = 0;
        for (int i = 0;i < n;i++) {
            prefix += differences[i];
            min_prefix = min(min_prefix,prefix);
            max_prefix = max(max_prefix,prefix);
        }
        // x ∈ [lower - min_prefix,upper - max_prefix]
        ll left = lower - min_prefix;
        ll right = upper - max_prefix;
        if (left > right) {
            return 0;
        }
        return right - left + 1;
    }
};

int main() {
    nums_of_arrays2145 sol;
    vector<int> differences = {4,-7,2};
    int lower = 3,upper = 6;
    int array_nums = sol.numsOfArraysRE(differences,lower,upper);
    cout << array_nums;
    return 0;
}
