#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    // 二分查找解法
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int lo = matrix[0][0];
        int hi = matrix[n-1][n-1];
        
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int count = countLessEqual(matrix, mid);
            if (count < k) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return lo;
    }
    
    int countLessEqual(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int i = n - 1;
        int j = 0;
        int count = 0;
        
        while (i >= 0 && j < n) {
            if (matrix[i][j] <= target) {
                count += i + 1; // 当前列中有i+1个元素小于等于target
                j++;
            } else {
                i--;
            }
        }
        return count;
    }
    
    // 最小堆解法
    int kthSmallestHeap(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        // 使用优先队列（最小堆）
        // 存储三元组 {值, 行, 列}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        
        // 将第一列的元素加入堆
        for (int i = 0; i < min(n, k); i++) {
            pq.push({matrix[i][0], i, 0});
        }
        
        // 弹出k-1个元素
        for (int i = 1; i < k; i++) {
            auto curr = pq.top();
            pq.pop();
            
            int row = curr[1];
            int col = curr[2];
            
            if (col + 1 < n) {
                pq.push({matrix[row][col + 1], row, col + 1});
            }
        }
        
        return pq.top()[0];
    }
};

// 测试函数
int main() {
    Solution sol;
    
    // 测试用例1
    vector<vector<int>> matrix1 = {
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15}
    };
    int k1 = 8;
    cout << "Binary Search: " << sol.kthSmallest(matrix1, k1) << endl;
    cout << "Heap: " << sol.kthSmallestHeap(matrix1, k1) << endl;
    
    // 测试用例2
    vector<vector<int>> matrix2 = {
        {1, 2},
        {1, 3}
    };
    int k2 = 2;
    cout << "Binary Search: " << sol.kthSmallest(matrix2, k2) << endl;
    cout << "Heap: " << sol.kthSmallestHeap(matrix2, k2) << endl;
    
    return 0;
}

/*
算法思路：
1. 二分查找解法：
   - 在矩阵的最小值和最大值之间进行二分查找
   - 对于每个中间值，计算矩阵中小于等于该值的元素个数
   - 如果个数小于k，说明第k小的元素在右半部分
   - 否则在左半部分
   - 时间复杂度：O(n * log(max-min))，其中n是矩阵的边长

2. 最小堆解法：
   - 将矩阵的第一列元素加入最小堆
   - 每次从堆中弹出最小元素，并将其右侧元素加入堆
   - 重复k-1次后，堆顶元素即为第k小的元素
   - 时间复杂度：O(k * log(n))，其中n是矩阵的边长
*/