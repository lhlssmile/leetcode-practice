/*
LeetCode 437. Path Sum III
给你一个二叉树的根节点 root 和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。
路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

示例 1：
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。

示例 2：
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3

提示：
- 二叉树的节点个数的范围是 [0,1000]
- -10^9 <= Node.val <= 10^9
- -1000 <= targetSum <= 1000
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // 方法1：前缀和 + 哈希表优化（推荐）
    // 时间复杂度：O(n)，空间复杂度：O(n)
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, int> prefixCount;
        prefixCount[0] = 1;  // 初始化：前缀和为0的路径有1条
        return dfs(root, 0, targetSum, prefixCount);
    }
    
private:
    int dfs(TreeNode* node, long long currentSum, int targetSum, unordered_map<long long, int>& prefixCount) {
        if (!node) return 0;
        
        // 更新当前路径的前缀和
        currentSum += node->val;
        
        // 查找是否存在前缀和为 (currentSum - targetSum) 的路径
        long long targetPrefix = currentSum - targetSum;
        int result = prefixCount.count(targetPrefix) ? prefixCount[targetPrefix] : 0;
        
        // 将当前前缀和加入哈希表
        prefixCount[currentSum]++;
        
        // 递归处理左右子树
        result += dfs(node->left, currentSum, targetSum, prefixCount);
        result += dfs(node->right, currentSum, targetSum, prefixCount);
        
        // 回溯：移除当前节点的贡献
        prefixCount[currentSum]--;
        if (prefixCount[currentSum] == 0) {
            prefixCount.erase(currentSum);
        }
        
        return result;
    }
    
public:
    // 方法2：暴力解法（用于对比）
    // 时间复杂度：O(n^2)，空间复杂度：O(n)
    int pathSumBruteForce(TreeNode* root, int targetSum) {
        if (!root) return 0;
        
        // 以当前节点为起点的路径数 + 左子树的路径数 + 右子树的路径数
        return pathFromNode(root, targetSum) + 
               pathSumBruteForce(root->left, targetSum) + 
               pathSumBruteForce(root->right, targetSum);
    }
    
private:
    int pathFromNode(TreeNode* node, long long targetSum) {
        if (!node) return 0;
        
        int count = 0;
        if (node->val == targetSum) count++;
        
        count += pathFromNode(node->left, targetSum - node->val);
        count += pathFromNode(node->right, targetSum - node->val);
        
        return count;
    }
    
public:
    // 调试版本：带详细输出的前缀和算法
    int pathSumDebug(TreeNode* root, int targetSum) {
        cout << "=== 开始调试版本的路径和算法 ===" << endl;
        unordered_map<long long, int> prefixCount;
        prefixCount[0] = 1;
        int result = dfsDebug(root, 0, targetSum, prefixCount, 0);
        cout << "=== 调试结束，总路径数：" << result << " ===" << endl;
        return result;
    }
    
private:
    int dfsDebug(TreeNode* node, long long currentSum, int targetSum, 
                 unordered_map<long long, int>& prefixCount, int depth) {
        if (!node) return 0;
        
        string indent(depth * 2, ' ');
        cout << indent << "访问节点：" << node->val << endl;
        
        currentSum += node->val;
        cout << indent << "当前前缀和：" << currentSum << endl;
        
        long long targetPrefix = currentSum - targetSum;
        int result = prefixCount.count(targetPrefix) ? prefixCount[targetPrefix] : 0;
        
        if (result > 0) {
            cout << indent << "找到 " << result << " 条路径！目标前缀：" << targetPrefix << endl;
        }
        
        prefixCount[currentSum]++;
        cout << indent << "前缀和计数器更新：[" << currentSum << "] = " << prefixCount[currentSum] << endl;
        
        result += dfsDebug(node->left, currentSum, targetSum, prefixCount, depth + 1);
        result += dfsDebug(node->right, currentSum, targetSum, prefixCount, depth + 1);
        
        prefixCount[currentSum]--;
        cout << indent << "回溯：[" << currentSum << "] = " << prefixCount[currentSum] << endl;
        if (prefixCount[currentSum] == 0) {
            prefixCount.erase(currentSum);
            cout << indent << "移除前缀和：" << currentSum << endl;
        }
        
        return result;
    }
};

// 辅助函数：从数组创建二叉树
TreeNode* createTreeFromArray(vector<int>& arr) {
    if (arr.empty() || arr[0] == INT_MIN) return nullptr;
    
    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < arr.size()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (i < arr.size() && arr[i] != INT_MIN) {
            node->left = new TreeNode(arr[i]);
            q.push(node->left);
        }
        i++;
        
        if (i < arr.size() && arr[i] != INT_MIN) {
            node->right = new TreeNode(arr[i]);
            q.push(node->right);
        }
        i++;
    }
    
    return root;
}

// 辅助函数：打印二叉树（前序遍历）
void printTreePreorder(TreeNode* root) {
    if (!root) {
        cout << "null ";
        return;
    }
    cout << root->val << " ";
    printTreePreorder(root->left);
    printTreePreorder(root->right);
}

int main() {
    Solution solution;
    
    cout << "\n=== C++ 版本路径和算法测试 ===\n" << endl;
    
    // 测试用例1
    cout << "测试用例1：" << endl;
    vector<int> tree1 = {10, 5, -3, 3, 2, INT_MIN, 11, 3, -2, INT_MIN, 1};
    TreeNode* root1 = createTreeFromArray(tree1);
    int targetSum1 = 8;
    
    cout << "输入树（前序遍历）：";
    printTreePreorder(root1);
    cout << "\n目标和：" << targetSum1 << endl;
    
    int result1_optimized = solution.pathSum(root1, targetSum1);
    int result1_brute = solution.pathSumBruteForce(root1, targetSum1);
    
    cout << "前缀和算法结果：" << result1_optimized << endl;
    cout << "暴力算法结果：" << result1_brute << endl;
    
    // 调试版本
    cout << "\n--- 调试过程 ---" << endl;
    solution.pathSumDebug(root1, targetSum1);
    
    cout << "\n" << string(50, '=') << "\n" << endl;
    
    // 测试用例2
    cout << "测试用例2：" << endl;
    vector<int> tree2 = {5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, 5, 1};
    TreeNode* root2 = createTreeFromArray(tree2);
    int targetSum2 = 22;
    
    cout << "输入树（前序遍历）：";
    printTreePreorder(root2);
    cout << "\n目标和：" << targetSum2 << endl;
    
    int result2_optimized = solution.pathSum(root2, targetSum2);
    int result2_brute = solution.pathSumBruteForce(root2, targetSum2);
    
    cout << "前缀和算法结果：" << result2_optimized << endl;
    cout << "暴力算法结果：" << result2_brute << endl;
    
    cout << "\n=== 算法分析 ===" << endl;
    cout << "前缀和算法：" << endl;
    cout << "- 时间复杂度：O(n)，每个节点访问一次" << endl;
    cout << "- 空间复杂度：O(n)，哈希表存储前缀和" << endl;
    cout << "- 核心思想：前缀和 + 哈希表 + 回溯" << endl;
    
    cout << "\n暴力算法：" << endl;
    cout << "- 时间复杂度：O(n^2)，每个节点都要遍历其子树" << endl;
    cout << "- 空间复杂度：O(n)，递归栈深度" << endl;
    cout << "- 核心思想：枚举所有可能的起点" << endl;
    
    cout << "\n推荐使用前缀和算法，效率更高！" << endl;
    
    return 0;
}

/*
编译和运行：
g++ -o pathSum pathSum.cpp
./pathSum

核心算法思想：
1. 前缀和：从根节点到当前节点的路径和
2. 哈希表：记录每个前缀和出现的次数
3. 路径查找：如果存在前缀和为 (当前前缀和 - 目标和) 的路径，
   说明从那个位置到当前节点的路径和等于目标和
4. 回溯：处理完当前节点后，要从哈希表中移除当前节点的贡献

时间复杂度：O(n)
空间复杂度：O(n)
*/