//
// Created by 24276 on 2025/8/4.
//

#include <unordered_map>
#include <vector>
using namespace std;
class delete_and_earn {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxVal = 0;
        for (int x : nums ) {
            maxVal = max(x, maxVal);
        }
        pmr::unordered_map<int, int> counts(maxVal + 1);
        for(int x : nums ) {
            counts[x] += x;
        }
        int dpPrev2 = 0, dpPrev1 = counts[1];

        for (int i = 2; i <= maxVal; i++) {
            int dpCurr = max(dpPrev2 + counts[i], dpPrev1);
            dpPrev2 = dpPrev1, dpPrev1 = dpCurr;
        }
        return dpPrev1;
    }
};