#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
/**
 * 给你一个整数 n，表示图中的节点数量，这些节点按从 0 到 n - 1 编号。

同时给你一个长度为 n 的整数数组 nums，该数组按 非递减 顺序排序，以及一个整数 maxDiff。

如果满足 |nums[i] - nums[j]| <= maxDiff（即 nums[i] 和 nums[j] 的 绝对差 至多为 maxDiff），则节点 i 和节点 j 之间存在一条 无向边 。

此外，给你一个二维整数数组 queries。对于每个 queries[i] = [ui, vi]，需要判断节点 ui 和 vi 之间是否存在路径。

返回一个布尔数组 answer，其中 answer[i] 等于 true 表示在第 i 个查询中节点 ui 和 vi 之间存在路径，否则为 false。

 

示例 1：

输入: n = 2, nums = [1,3], maxDiff = 1, queries = [[0,0],[0,1]]

输出: [true,false]

解释:

查询 [0,0]：节点 0 有一条到自己的显然路径。
查询 [0,1]：节点 0 和节点 1 之间没有边，因为 |nums[0] - nums[1]| = |1 - 3| = 2，大于 maxDiff。
因此，在处理完所有查询后，最终答案为 [true, false]。
示例 2：

输入: n = 4, nums = [2,5,6,8], maxDiff = 2, queries = [[0,1],[0,2],[1,3],[2,3]]

输出: [false,false,true,true]

解释:

生成的图如下：



查询 [0,1]：节点 0 和节点 1 之间没有边，因为 |nums[0] - nums[1]| = |2 - 5| = 3，大于 maxDiff。
查询 [0,2]：节点 0 和节点 2 之间没有边，因为 |nums[0] - nums[2]| = |2 - 6| = 4，大于 maxDiff。
查询 [1,3]：节点 1 和节点 3 之间存在路径通过节点 2，因为 |nums[1] - nums[2]| = |5 - 6| = 1 和 |nums[2] - nums[3]| = |6 - 8| = 2，都小于等于 maxDiff。
查询 [2,3]：节点 2 和节点 3 之间有一条边，因为 |nums[2] - nums[3]| = |6 - 8| = 2，等于 maxDiff。
因此，在处理完所有查询后，最终答案为 [false, false, true, true]。
 

提示：

1 <= n == nums.length <= 105
0 <= nums[i] <= 105
nums 按 非递减 顺序排序。
0 <= maxDiff <= 105
1 <= queries.length <= 105
queries[i] == [ui, vi]
0 <= ui, vi < n
 */

class Solution {
private:
    int find(vector<int>& parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> parent(n);
        vector<int> rank(n, 0);
        
        // 初始化并查集
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        // 使用双指针来找到所有满足条件的节点对
        int j = 0;
        for (int i = 0; i < n; i++) {
            // 找到第一个不满足条件的j
            while (j < n && nums[j] - nums[i] <= maxDiff) {
                j++;
            }
            
            // 将i与i+1到j-1的所有节点合并
            if (i + 1 < j) {
                unionSets(parent, rank, i, i + 1);
            }
        }
        
        // 处理查询
        vector<bool> result;
        for (const auto& query : queries) {
            int u = query[0], v = query[1];
            result.push_back(find(parent, u) == find(parent, v));
        }
        
        return result;
    }
};

int main() {
    // 测试用例1
    Solution sol;
    vector<int> nums1 = {1, 3};
    vector<vector<int>> queries1 = {{0, 0}, {0, 1}};
    vector<bool> result1 = sol.pathExistenceQueries(2, nums1, 1, queries1);
    cout << "Test case 1: ";
    for (bool b : result1) cout << (b ? "true " : "false ");
    cout << endl;
    
    // 测试用例2
    vector<int> nums2 = {2, 5, 6, 8};
    vector<vector<int>> queries2 = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    vector<bool> result2 = sol.pathExistenceQueries(4, nums2, 2, queries2);
    cout << "Test case 2: ";
    for (bool b : result2) cout << (b ? "true " : "false ");
    cout << endl;
    
    return 0;
}