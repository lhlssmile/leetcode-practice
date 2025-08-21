//
// Created by 24276 on 2025/8/21.
//
#include <bits/stdc++.h>
using namespace std;
#include <vector>
class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<array<int, 3>> a; // {nums1[i], nums2[i], i}
        for (int i = 0; i < n; i++) {
            a.push_back({nums1[i], nums2[i], i});
        }
        sort(a.begin(), a.end()); // 按 nums1 升序

        vector<long long> ans(n, 0);
        priority_queue<int, vector<int>, greater<int>> pq; // 小顶堆
        long long sum_heap = 0;

        int i = 0;
        while (i < n) {
            int j = i;
            // 找到相同 nums1 的区间 [i, j)
            while (j < n && a[j][0] == a[i][0]) j++;

            // 先给这一组的答案（不包含同组元素）
            for (int t = i; t < j; t++) {
                ans[a[t][2]] = sum_heap;
            }

            // 再把这一组的 nums2 加入堆
            for (int t = i; t < j; t++) {
                int val = a[t][1];
                if ((int)pq.size() < k) {
                    pq.push(val);
                    sum_heap += val;
                } else if (!pq.empty() && pq.top() < val) {
                    sum_heap -= pq.top();
                    pq.pop();
                    pq.push(val);
                    sum_heap += val;
                }
            }

            i = j;
        }
        return ans;
    }
};
int main() {
    Solution s;
    vector<int> nums1 = {4,2,1,5,3}, nums2 = {10,20,30,40,50}; int k = 2;
    s.findMaxSum(nums1, nums2, k);
}