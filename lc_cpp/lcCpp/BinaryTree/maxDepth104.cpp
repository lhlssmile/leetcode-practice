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

class max_depth104 {
public:
    int maxDepth(TreeNode* root) {
        int ans = 0;
        //通用引用（Universal Reference），也称为 转发引用（Forwarding Reference）。它的作用是让 lambda 表达式能够递归调用自身。
        auto dfs = [&](auto&& dfs, TreeNode* node, int depth) -> void {
            if (node == nullptr) {
                return;
            }
            depth++;
            ans = max(ans, depth);
            dfs(dfs,node->left, depth);
            dfs(dfs,node->right, depth);
        };
        dfs(dfs,root, 0);
        return ans;
    }
    bool isSameTree(TreeNode* p,TreeNode* q) {
        auto dfs = [&](auto&& dfs,TreeNode* p,TreeNode* q) -> bool {
            if(p == nullptr || q == nullptr) {
                //此时已经不相同了
                return p == q;
            }
            return dfs(dfs,p->left,q->left) && dfs(dfs,p->right,q->right)
            && p->val == q->val;
        };
        return dfs(dfs,p,q);
    }
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return isSameTreeUsed(root->left,root->right);
    }
    bool isSameTreeUsed(TreeNode* p,TreeNode* q){
        auto dfs = [&](auto&& dfs,TreeNode* p,TreeNode* q) -> bool {
            if(p == nullptr || q == nullptr){
                return p == q;
            }
            return dfs(dfs,p->left,q->right) && dfs(dfs,p->right,q->left) && p->val == q->val;
        };
        return dfs(dfs,p,q);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder_tree;
        auto dfs = [&](auto&& dfs,TreeNode* root) {
            if(root == nullptr) {
                return ;
            }
            dfs(dfs,root->left);
            inorder_tree.push_back(root->val);
            dfs(dfs,root->right);
        };
        dfs(dfs,root);
        return inorder_tree;
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> level_order_tree;
        if(root == nullptr) return {{}};
        std::queue<TreeNode* > queue;
        //先把根放到队列里
        queue.push(root);
        while(!queue.empty()) {
            auto level_size = queue.size();
            vector<int> current_vector;
            for(int i = 0;i < level_size;++i) {
                auto* node = queue.front();
                queue.pop();
                current_vector.push_back(node->val);
                if(node->left) queue.push(node->left);
                if(node->right) queue.push(node->right);
            }
            level_order_tree.push_back(current_vector);
        }
        return level_order_tree;
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

    // 示例输入：层序遍历的节点值，-1 表示空节点
    vector<int> values = {1, 2, 3, -1, 4, 5, 6};  // 表示的树结构：
                                                  //        1
                                                  //       / \
                                                  //      2   3
                                                  //       \ / \
                                                  //       4 5 6
    vector<int> values2 = {1,2,3,4,-1,5,6};
    vector<int> values3 = {1,2,2};
    // 创建树
    TreeNode* root = createTree(values);
    // auto* q = createTree(values2);
    // auto* symmetricTree = createTree(values3);
    max_depth104 ps;
    // int max_depth = ps.maxDepth(root);
    // cout << "max_depth:" << max_depth <<  endl;
    // cout << " is Same:" << ps.isSameTree(root,q) << endl;
    // cout << "is symmetric:" << ps.isSymmetric(symmetricTree) << endl;


    auto res = ps.inorderTraversal(root);
    for(auto const node : res) {
        cout << node << " ";
    }
    cout << "-------------------" << endl;

    ps.levelOrder(root);
    cout << "-------------------" << endl;
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

    printTree(root);

    return 0;
}