//
// Created by 24276 on 2025/4/2.
//

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class max_sliding_window239 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums,int k) {
        int n = nums.size();
        vector<int> res;

        if (n == 0 || k == 0) return res;

        if (n < k) {
            // 如果数组长度小于k，只需返回整个数组的最大值
            int maxVal = nums[0];
            for (int i = 1; i < n; i++) {
                maxVal = max(maxVal, nums[i]);
            }
            res.push_back(maxVal);
            return res;
        }

        deque<int> dq; // 存储索引，而不是值

        // 处理第一个窗口
        for (int i = 0; i < k; i++) {
            // 保持队列单调递减，移除所有小于当前元素的值
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }

        // 第一个窗口的最大值
        res.push_back(nums[dq.front()]);

        // 处理剩余窗口
        for (int i = k; i < n; i++) {
            // 移除已经不在当前窗口的元素
            if (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // 保持队列单调递减
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);

            // 当前窗口的最大值
            res.push_back(nums[dq.front()]);
        }

        return res;
    }

};

int main() {
    max_sliding_window239 solution;
    int k = 3;
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    auto res = solution.maxSlidingWindow(nums,k);
    for (auto ele : res) {
        cout << ele << " ";
    }
    return 0;
}
