#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
【LeetCode 215】数组中的第K个最大元素 - 小根堆解法

题目：给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
要求：时间复杂度 O(n)

核心思路：
1. 维护一个大小为 k 的小根堆
2. 堆中始终保存当前最大的 k 个元素
3. 堆顶就是第 k 大的元素

为什么用小根堆？
- 我们要找第 k 大的元素
- 维护一个包含最大 k 个元素的集合
- 在这个集合中，最小的那个就是第 k 大的元素
- 小根堆的堆顶恰好是最小元素
*/

class Solution {
public:
    // 方法一：使用 STL 的 priority_queue（推荐）
    int findKthLargest(vector<int>& nums, int k) {
        // C++ 的 priority_queue 默认是大根堆
        // 我们需要小根堆，使用 greater<int> 比较器
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        for (int num : nums) {
            if (minHeap.size() < k) {
                minHeap.push(num);
            } else if (num > minHeap.top()) {
                minHeap.pop();   // 弹出最小的
                minHeap.push(num); // 加入更大的
            }
        }
        
        return minHeap.top(); // 堆顶就是第 k 大的元素
    }
    
    // 方法二：手动实现小根堆（教学用）
    int findKthLargestManual(vector<int>& nums, int k) {
        vector<int> heap;
        
        for (int num : nums) {
            if (heap.size() < k) {
                heap.push_back(num);
                push_heap(heap.begin(), heap.end(), greater<int>());
            } else if (num > heap[0]) {
                pop_heap(heap.begin(), heap.end(), greater<int>());
                heap.pop_back();
                heap.push_back(num);
                push_heap(heap.begin(), heap.end(), greater<int>());
            }
        }
        
        return heap[0];
    }
    
    // 方法三：大根堆解法（对比学习）
    int findKthLargestMaxHeap(vector<int>& nums, int k) {
        // 使用大根堆，弹出前 k-1 个最大元素
        priority_queue<int> maxHeap(nums.begin(), nums.end());
        
        for (int i = 0; i < k - 1; i++) {
            maxHeap.pop();
        }
        
        return maxHeap.top();
    }
};

// 手动实现小根堆类（完整版）
class MinHeap {
private:
    vector<int> heap;
    
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent]) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }
            
            if (smallest == index) break;
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }
    
public:
    void push(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }
    
    int top() {
        return heap.empty() ? -1 : heap[0];
    }
    
    int size() {
        return heap.size();
    }
    
    bool empty() {
        return heap.empty();
    }
};

// 使用自定义小根堆的解法
class SolutionCustom {
public:
    int findKthLargest(vector<int>& nums, int k) {
        MinHeap minHeap;
        
        for (int num : nums) {
            if (minHeap.size() < k) {
                minHeap.push(num);
            } else if (num > minHeap.top()) {
                minHeap.pop();
                minHeap.push(num);
            }
        }
        
        return minHeap.top();
    }
};

// 测试函数
void testSolution() {
    Solution sol;
    
    // 测试用例 1
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    cout << "测试用例 1: [3,2,1,5,6,4], k=2" << endl;
    cout << "结果: " << sol.findKthLargest(nums1, k1) << " (期望: 5)" << endl;
    cout << endl;
    
    // 测试用例 2
    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    cout << "测试用例 2: [3,2,3,1,2,4,5,5,6], k=4" << endl;
    cout << "结果: " << sol.findKthLargest(nums2, k2) << " (期望: 4)" << endl;
    cout << endl;
    
    // 对比三种方法
    vector<int> nums3 = {7, 10, 4, 3, 20, 15};
    int k3 = 3;
    cout << "对比测试: [7,10,4,3,20,15], k=3" << endl;
    cout << "小根堆方法: " << sol.findKthLargest(nums3, k3) << endl;
    cout << "手动堆方法: " << sol.findKthLargestManual(nums3, k3) << endl;
    cout << "大根堆方法: " << sol.findKthLargestMaxHeap(nums3, k3) << endl;
    cout << "期望结果: 10" << endl;
}

int main() {
    cout << "=== C++ 小根堆解决第K个最大元素问题 ===" << endl;
    cout << endl;
    
    testSolution();
    
    cout << "\n=== 堆的基本概念 ===" << endl;
    cout << "1. 小根堆：父节点 <= 子节点，堆顶是最小元素" << endl;
    cout << "2. 大根堆：父节点 >= 子节点，堆顶是最大元素" << endl;
    cout << "3. C++ STL:" << endl;
    cout << "   - priority_queue<int>: 默认大根堆" << endl;
    cout << "   - priority_queue<int, vector<int>, greater<int>>: 小根堆" << endl;
    cout << "4. 时间复杂度：" << endl;
    cout << "   - 插入/删除: O(log n)" << endl;
    cout << "   - 建堆: O(n)" << endl;
    cout << "   - 查看堆顶: O(1)" << endl;
    
    return 0;
}

/*
编译运行：
g++ -o findKthLargest findKthLargest215.cpp
./findKthLargest

输出示例：
=== C++ 小根堆解决第K个最大元素问题 ===

测试用例 1: [3,2,1,5,6,4], k=2
结果: 5 (期望: 5)

测试用例 2: [3,2,3,1,2,4,5,5,6], k=4
结果: 4 (期望: 4)

对比测试: [7,10,4,3,20,15], k=3
小根堆方法: 10
手动堆方法: 10
大根堆方法: 10
期望结果: 10

=== 堆的基本概念 ===
1. 小根堆：父节点 <= 子节点，堆顶是最小元素
2. 大根堆：父节点 >= 子节点，堆顶是最大元素
3. C++ STL:
   - priority_queue<int>: 默认大根堆
   - priority_queue<int, vector<int>, greater<int>>: 小根堆
4. 时间复杂度：
   - 插入/删除: O(log n)
   - 建堆: O(n)
   - 查看堆顶: O(1)
*/