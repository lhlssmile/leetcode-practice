//
// Created by 24276 on 2025/4/4.
//
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;TreeNode* right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int val):val(val),left(nullptr),right(nullptr){}
    TreeNode(int val,TreeNode* left,TreeNode* right):val(val),left(left),right(right){}
};
// 与865题相同
class lca_deepest_leaves1123 {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        /**
         * 找到树的最大深度 找到最深层的叶子的最近公共祖先(最深叶子的父?
         * 对于遍历到的每个node 都计算它的左右子树深度和最深叶子的公共祖先
         * 若左子树更深 那么最近公共祖先在左子树 否则在右子树
         */
        pair<int,TreeNode*> result = helper(root,0);
        return result.second;
    }
    pair<int,TreeNode*> helper(TreeNode* root,int depth) {
        //若是空树?没有祖先 也没有深度
        if (!root) return {depth - 1,nullptr};
        if (!root->left && !root->right) {
            //此节点为叶子
            return {depth,root};
        }
        //递归左右子树 看谁的深度大?
        auto left = helper(root->left,depth + 1);
        auto right = helper(root->right,depth + 1);
        if (left.first == right.first) {
            return {left.first,root};
        }else if(left.first > right.first) {
            return left;
        }else {
            return right;
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder_tree;
        auto dfs = [&](auto&& dfs,TreeNode* root) {
            if(root == nullptr) {
                return ;
            }
            dfs(dfs,root->left);
            cout << root->val;
            inorder_tree.push_back(root->val);
            dfs(dfs,root->right);
        };
        dfs(dfs,root);
        return inorder_tree;
    }
};
int main() {
    // 创建树的 lambda 表达式
    auto createTree = [](const vector<int>& values) -> TreeNode* {
        if (values.empty() || values[0] == -1) return nullptr;  // 空树

        TreeNode* root = new TreeNode(values[0]);  // 创建根节点
        queue<TreeNode*> q;
        q.push(root);

        int index = 1;  // 从第二个值开始
        while (!q.empty() && index < values.size()) {
            TreeNode* current = q.front();
            q.pop();

            // 处理左子节点
            if (index < values.size() && values[index] != -1) {
                current->left = new TreeNode(values[index]);
                q.push(current->left);
            }
            index++;

            // 处理右子节点
            if (index < values.size() && values[index] != -1) {
                current->right = new TreeNode(values[index]);
                q.push(current->right);
            }
            index++;
        }

        return root;
    };
    vector<int> values = {3,5,1,6,2,0,8,-1,-1,7,4};
    auto* tree = createTree(values);
    lca_deepest_leaves1123 solution;
    auto* res = solution.lcaDeepestLeaves(tree);
    solution.inorderTraversal(res);
    return 0;
}
