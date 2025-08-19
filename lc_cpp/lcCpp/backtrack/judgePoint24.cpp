//
// Created by 24276 on 2025/8/18.
//
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
#define pb push_back
class Solution {
    const int RES = 24;
    const double EPS = 1e-6;
public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums;
        for (int x : cards) nums.pb(x);
        return solve(nums);
    }
private:
    bool solve(vector<double>& nums) {
        int n = nums.size();
        if (n == 1) return fabs(nums[0] - 24.0) < EPS;

        for (int i = 0; i < n;i++) {
            for (int j = i + 1; j < n; j++) {
                vector<double> nxt;
                for (int k = 0; k < n; k++) {
                    if (k != i && k != j) nxt.pb(nums[k]);
                }
                for (double x : compute(nums[i], nums[j])) {
                    nxt.pb(x);
                    if (solve(nxt)) return true;
                    nxt.pop_back();
                }
            }
        }
        return false;
    }
    vector<double> compute(double a, double b) {
        vector<double> res;
        res.push_back(a + b);
        res.push_back(a - b);
        res.push_back(b - a);
        res.push_back(a * b);
        if (fabs(b) > EPS) res.push_back(a / b);
        if (fabs(a) > EPS) res.push_back(b / a);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> cards = {4, 1, 8, 7};
    s.judgePoint24(cards);
    return 0;
}
