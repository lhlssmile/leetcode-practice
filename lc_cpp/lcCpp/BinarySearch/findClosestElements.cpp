#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    // 方法1: 二分扩展法
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        
        int left = idx - 1, right = idx;
        
        while (right - left - 1 < k) {
            if (left < 0) {
                right++;
            } else if (right >= n) {
                left--;
            } else {
                if (x - arr[left] <= arr[right] - x) {
                    left--;
                } else {
                    right++;
                }
            }
        }
        
        return vector<int>(arr.begin() + left + 1, arr.begin() + right);
    }
    
    // 方法2: 滑动窗口法
    vector<int> findClosestElementsSlidingWindow(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size() - k;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (x - arr[mid] > arr[mid + k] - x) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
    
    // 方法3: 大根堆法
    vector<int> findClosestElementsMaxHeap(vector<int>& arr, int k, int x) {
        // 使用优先队列实现大根堆
        priority_queue<pair<int, int>> pq; // {distance, value}
        
        for (int num : arr) {
            int distance = abs(num - x);
            if (pq.size() < k) {
                pq.push({distance, num});
            } else if (distance < pq.top().first || 
                      (distance == pq.top().first && num < pq.top().second)) {
                pq.pop();
                pq.push({distance, num});
            }
        }
        
        vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        
        sort(result.begin(), result.end());
        return result;
    }
    
    // 方法3优化: 大根堆法 - 提前终止
    vector<int> findClosestElementsOptimizedHeap(vector<int>& arr, int k, int x) {
        priority_queue<pair<int, pair<int, int>>> pq; // {distance, {value, index}}
        
        for (int i = 0; i < arr.size(); i++) {
            int distance = abs(arr[i] - x);
            if (pq.size() < k) {
                pq.push({distance, {arr[i], i}});
            } else if (distance < pq.top().first || 
                      (distance == pq.top().first && arr[i] < pq.top().second.first)) {
                pq.pop();
                pq.push({distance, {arr[i], i}});
            } else if (distance > pq.top().first) {
                break; // 提前终止
            }
        }
        
        vector<pair<int, int>> temp;
        while (!pq.empty()) {
            temp.push_back({pq.top().second.second, pq.top().second.first});
            pq.pop();
        }
        
        sort(temp.begin(), temp.end());
        vector<int> result;
        for (auto& p : temp) {
            result.push_back(p.second);
        }
        return result;
    }
};

void test() {
    Solution sol;
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 4, x = 3;
    
    auto res1 = sol.findClosestElements(arr, k, x);
    cout << "二分扩展法: ";
    for (int num : res1) cout << num << " ";
    cout << endl;
    
    auto res2 = sol.findClosestElementsSlidingWindow(arr, k, x);
    cout << "滑动窗口法: ";
    for (int num : res2) cout << num << " ";
    cout << endl;
    
    auto res3 = sol.findClosestElementsMaxHeap(arr, k, x);
    cout << "大根堆法: ";
    for (int num : res3) cout << num << " ";
    cout << endl;
}

int main() {
    test();
    return 0;
}