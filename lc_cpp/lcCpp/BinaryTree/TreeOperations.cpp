#include <stack>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;TreeNode* right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int val):val(val),left(nullptr),right(nullptr){}
    TreeNode(int val,TreeNode* left,TreeNode* right):val(val),left(left),right(right){}
};
class tree_operations {
public:
    //Recurision
    void flatten(TreeNode* root) {
        //ex:当前
        if(!root) return;

        flatten(root->left);
        flatten(root->right);
        //  🌸🌸反转完了 能不能优化?如果这个右子树为空 直接退回上一个node?
        // 这里不要为空直接跳出递归 因为要赋 null
        auto* right_sub_tree = root->right;

        root->right = root->left;
        root->left = nullptr;

        auto* current = root;
        while(current->right) {
            current = current->right;
        }
        current->right = right_sub_tree;
    }
    //stack
    void flattens(TreeNode* root) {
        if(!root) return;
        std::stack<TreeNode* > stack;
        stack.push(root);
        TreeNode* prev = nullptr;
        while(!stack.empty()) {
            auto* current = stack.top();
            stack.pop();
            if(prev) {
                prev->right = current;
                prev->left = nullptr;
            }
            if(current->right) stack.push(current->right);
            if(current->left)   stack.push(current->left);
            prev = current;
        }
    }
    //分治
    void flattens2(TreeNode* root) {
        dfs(root);
    }
private:
    TreeNode* dfs(TreeNode* root) {
        if(root == nullptr) {
            return nullptr;
        }
        TreeNode* left_tail = dfs(root->left);
        TreeNode* right_tail = dfs(root->right);
        if(left_tail) {
            left_tail->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
        return right_tail ? right_tail : left_tail ? left_tail : root;
    }
};
int main(){
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
    vector<int> values = {1,2,5,3,4,-1,6};
    auto* tree = createTree(values);





    /**
     *Test Code Scope
     */
    tree_operations ps;
    ps.flattens2(tree);























    // 打印树的层序遍历结果（优化后的打印函数）
    auto printTree = [](TreeNode* root) {
        if (!root) {
            cout << "树为空！" << endl;
            return;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node) {
                    cout << node->val << " ";
                    q.push(node->left);
                    q.push(node->right);
                } else {
                    cout << "null ";  // 打印空节点
                }
            }
            cout << endl;  // 换行表示一层结束
        }
    };
    printTree(tree);
}