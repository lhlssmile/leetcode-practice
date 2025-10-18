struct Node {
    Node* left;
    Node* right;
    bool cover;
    int lazy;
    Node():left(nullptr), right(nullptr), cover(false), lazy(0) {}
};  
class RangeModule {
    const int N = 1e9;
private:
    void update(Node* node, int start, int end, int l, int r, bool var) {
        if (l >= end || r <= start) return ;
        if (l <= start && end <= r) {
            node->cover = var;
            node->lazy = var ? 1 : -1;  
            return;
        }
        pushDown(node);
        int mid = (start + end) >> 1;
        update(node->left, start, mid, l, r, var);
        update(node->right, mid, end, l, r, var);
        node->cover = node->left->cover && node->right->cover;
    }
    void pushDown(Node* node) {
        if (node->left == nullptr) {
            node->left = new Node();
            node->right = new Node();
        }
        if (node->lazy == 1) {
            node->left->cover = true;
            node->right->cover = true;
            node->left->lazy = 1;
            node->right->lazy = 1;
            node->lazy = 0;
        }else if (node->lazy == -1) {
            node->left->cover = false;
            node->right->cover = false;
            node->left->lazy = -1;
            node->right->lazy = -1;
            node->lazy = 0;
        }
    }
    bool query(Node* node, int start, int end, int l, int r) {
        
        if (l >= end || r <= start) return true;  // 无交集，返回中性元（true for AND）
        if (l <= start && end <= r) {
            return node->cover;  // 全覆盖，直接返回 cover
        }
        // 部分重叠：先检查 lazy（优化：如果有 pending lazy，整个子树已设置，直接返回）
        if (node->lazy == 1) return true;
        if (node->lazy == -1) return false;
        // lazy == 0，部分重叠：推送到子节点（创建如果不存在），然后递归
        pushDown(node);
        int mid = (start + end) >> 1;
        bool leftRes = query(node->left, start, mid, l, r);
        bool rightRes = query(node->right, mid, end, l, r);  // 修正：end 而非 r
        return leftRes && rightRes;
    }
public:
    Node* root;
    RangeModule() {
        root = new Node();
    }
    
    void addRange(int left, int right) {
        update(root, 1, N, left, right, true);
    }
    
    bool queryRange(int left, int right) {
        return query(root, 1, N, left, right);
    }
    
    void removeRange(int left, int right) {
        update(root, 1, N, left, right, false);
    }
};

int main() {

    return 0;
}

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */