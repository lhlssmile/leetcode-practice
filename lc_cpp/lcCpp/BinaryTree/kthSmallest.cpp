//
// Created by 24276 on 2025/7/20.
//

#include <functional>
#include <stack>
#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // 方法1：递归版本（提前终止）
    int kthSmallest(TreeNode* root, int k) {
        if (!root || k <= 0) return -1; // 错误处理
        
        int count = 0;
        TreeNode* res = nullptr;
        
        std::function<void(TreeNode*)> inorderEarlyStop = [&](TreeNode* node) -> void {
            if (node == nullptr || res != nullptr) {
                return;
            }
            inorderEarlyStop(node->left);

            count++;
            if (count == k) {
                res = node;
                return; // 提前终止
            }
            inorderEarlyStop(node->right);
        };
        
        inorderEarlyStop(root);
        return res ? res->val : -1; // 安全检查
    }
    
    // 方法2：迭代版本（推荐，避免递归栈溢出）
    int kthSmallestIterative(TreeNode* root, int k) {
        if (!root || k <= 0) return -1;
        
        std::stack<TreeNode*> stk;
        TreeNode* curr = root;
        int count = 0;
        
        while (curr || !stk.empty()) {
            // 一直向左走到底
            while (curr) {
                stk.push(curr);
                curr = curr->left;
            }
            
            // 处理当前节点
            curr = stk.top();
            stk.pop();
            
            count++;
            if (count == k) {
                return curr->val;
            }
            
            // 转向右子树
            curr = curr->right;
        }
        
        return -1; // k超出范围
    }
    
    // 方法3：Morris遍历（O(1)空间复杂度）
    int kthSmallestMorris(TreeNode* root, int k) {
        if (!root || k <= 0) return -1;
        
        TreeNode* curr = root;
        int count = 0;
        
        while (curr) {
            if (!curr->left) {
                // 访问当前节点
                count++;
                if (count == k) {
                    return curr->val;
                }
                curr = curr->right;
            } else {
                // 找到前驱节点
                TreeNode* predecessor = curr->left;
                while (predecessor->right && predecessor->right != curr) {
                    predecessor = predecessor->right;
                }
                
                if (!predecessor->right) {
                    // 建立线索
                    predecessor->right = curr;
                    curr = curr->left;
                } else {
                    // 恢复树结构并访问节点
                    predecessor->right = nullptr;
                    count++;
                    if (count == k) {
                        return curr->val;
                    }
                    curr = curr->right;
                }
            }
        }
        
        return -1;
    }
};

// 辅助函数：构建测试树
TreeNode* buildTestTree() {
    /*
     构建测试树：
           3
          / \
         1   4
          \
           2
     中序遍历：1, 2, 3, 4
     */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(2);
    return root;
}

// 辅助函数：释放树内存
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Solution solution;
    TreeNode* root = buildTestTree();
    
    std::cout << "=== BST kth Smallest Element Test ===\n";
     std::cout << "Test tree inorder traversal should be: 1, 2, 3, 4\n\n";
    
    // 测试所有方法
    std::vector<int> testCases = {1, 2, 3, 4, 5}; // 包含边界情况
    
    for (int k : testCases) {
        std::cout << "k = " << k << ":\n";
         
         int result1 = solution.kthSmallest(root, k);
         int result2 = solution.kthSmallestIterative(root, k);
         int result3 = solution.kthSmallestMorris(root, k);
         
         std::cout << "  Recursive: " << result1 << "\n";
         std::cout << "  Iterative: " << result2 << "\n";
         std::cout << "  Morris: " << result3 << "\n";
         
         // Verify consistency
         if (result1 == result2 && result2 == result3) {
             std::cout << "  ✓ All methods consistent\n";
         } else {
             std::cout << "  ✗ Results inconsistent!\n";
         }
        std::cout << "\n";
    }
    
    deleteTree(root);
    return 0;
}

/*
=== Code Quality Enhancement Suggestions ===

1. Error Handling
   - Add null pointer checks
   - Handle k out of range cases
   - Return error codes instead of crashing

2. Memory Management
   - Provide tree construction and destruction functions
   - Avoid memory leaks
   - Use smart pointers (optional)

3. Performance Optimization
   - Iterative version avoids recursion stack overflow
   - Morris traversal achieves O(1) space complexity
   - Early termination reduces unnecessary computation

4. Code Maintainability
   - Clear function naming
   - Detailed comments
   - Modular design
   - Unit test coverage

5. Extensibility
   - Support different data types
   - Provide multiple implementation approaches
   - Easy integration into larger systems

6. Compilation Optimization
   - Use modern C++ features
   - Compiler optimization flags
   - Static analysis tool checks

Time Complexity Comparison:
- Recursive/Iterative: O(H + k) where H is tree height
- Morris Traversal: O(n) but O(1) space
- Best case: O(log n + k) for balanced trees

Space Complexity:
- Recursive: O(H) for call stack
- Iterative: O(H) for explicit stack
- Morris: O(1) constant space
*/
