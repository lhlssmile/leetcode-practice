//
// Created by 24276 on 2025/8/12.
//

#include <vector>
using namespace std;
class max_subarray_sum_circular {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int total = 0, mxEn = 0, meEn = 0, mxSum = nums[0], miSum = nums[0];
        for (int v : nums ) {
            total += v;
            mxEn = max(v, v + mxEn), mxSum = max(mxSum, mxEn),
            meEn = min(v, v + meEn), miSum = min(miSum, meEn);

        }
        if (mxSum < 0) return mxSum;
        return max(mxSum, total - miSum);
    }
};

int main() {

    return 0;
}
