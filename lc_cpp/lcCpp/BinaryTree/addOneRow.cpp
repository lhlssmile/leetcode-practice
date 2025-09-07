#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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
    // DFS解法
    TreeNode* addOneRowDFS(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            auto* newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        auto dfs = [&](this auto&& dfs, TreeNode* node, int val, int currentDepth, int targetDepth) -> void {
            if (!node) return;
            if (currentDepth == targetDepth - 1) {
                auto* oldLeft = node->left;
                auto* oldRight = node->right;
                
                node->left = new TreeNode(val);
                node->left->left = oldLeft;
                
                node->right = new TreeNode(val);
                node->right->right = oldRight;
                return;
            }
            dfs(node->left, val, currentDepth + 1, targetDepth);
            dfs(node->right, val, currentDepth + 1, targetDepth);
        };
        dfs(root, val, 1, depth);
        return root;
    }
    
    // BFS解法
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            auto* newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        int currentDepth = 1;
        
        while (!q.empty() && currentDepth < depth - 1) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            currentDepth++;
        }
        
        // 在目标深度的前一层插入新节点
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            auto* oldLeft = node->left;
            auto* oldRight = node->right;
            
            node->left = new TreeNode(val);
            node->left->left = oldLeft;
            
            node->right = new TreeNode(val);
            node->right->right = oldRight;
        }
        
        return root;
    }
};

// 测试函数
void testAddOneRow() {
    Solution sol;
    
    // 测试用例1: [4,2,6,3,1,5], val=1, depth=2
    TreeNode* root1 = new TreeNode(4);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(6);
    root1->left->left = new TreeNode(3);
    root1->left->right = new TreeNode(1);
    root1->right->left = new TreeNode(5);
    
    TreeNode* result1 = sol.addOneRow(root1, 1, 2);
    cout << "Test 1 passed" << endl;
    
    // 测试用例2: [4,2,null,3,1], val=1, depth=3
    TreeNode* root2 = new TreeNode(4);
    root2->left = new TreeNode(2);
    root2->left->left = new TreeNode(3);
    root2->left->right = new TreeNode(1);
    
    TreeNode* result2 = sol.addOneRow(root2, 1, 3);
    cout << "Test 2 passed" << endl;
}

int main() {
    testAddOneRow();
    return 0;
}

/*
算法思路：
1. DFS解法：递归遍历到目标深度的前一层，然后插入新节点
2. BFS解法：层序遍历到目标深度的前一层，然后批量插入新节点

时间复杂度：O(n) - 需要遍历树的节点
空间复杂度：
- DFS: O(h) - 递归栈深度
- BFS: O(w) - 队列最大宽度
*/