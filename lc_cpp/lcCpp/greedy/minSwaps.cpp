//
// Created by 24276 on 2025/8/18.
//

#define pb push_back
#define V vector
#include <climits>
#include <vector>
using namespace std;
typedef std::vector<int> vi;
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        vi evenPos, oddPos;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2) oddPos.pb(i);
            else evenPos.pb(i);
        }
        int es = evenPos.size(), os = oddPos.size();
        if ( abs(es - os)> 1) return -1;
        int res = INT_MAX;
        int pos = 0;
        //
        if (evenPos.size() >= oddPos.size()) {
            int cost = 0;
            for (int i = 0; i < evenPos.size();i++) {
                cost += abs(evenPos[i] - pos);
                pos += 2;
            }
            res = min(res, cost);
        }
        pos = 0;
        if (oddPos.size() >= evenPos.size()) {
            int cost = 0;
            for (int i = 0; i < oddPos.size(); i++) {
                cost += abs(oddPos[i] - pos);
                pos += 2;
            }
            res = min(res, cost);
        }
        return res;
    }
};