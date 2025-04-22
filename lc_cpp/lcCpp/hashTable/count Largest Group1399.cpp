//
// Created by 24276 on 2025/4/23.
//



#include <iostream>
#include <vector>
using namespace std;

class count_largest_group1399 {
public:
    /**
     * n <= 1e4 -> 10000 数位和最大是5?
     * @param n
     * @return
     */
    int countLargestGroup(int n) {
        vector<int> digitSum(n + 1, 0);
        vector<int> count(37, 0); // 数位和最大为 36

        for (int i = 1; i <= n; ++i) {
            digitSum[i] = digitSum[i / 10] + i % 10; // 动态计算数位和
            count[digitSum[i]]++;
        }

        int maxCount = *max_element(count.begin(), count.end());

        return count_if(count.begin(), count.end(), [maxCount](int c) {
            return c == maxCount;
        });
    }
};

int main() {
    count_largest_group1399 sol;
    int n = 13;
    cout << sol.countLargestGroup(n);
    return 0;
}
