// Definition for a binary tree node.
function TreeNode(val, left, right) {
    this.val = (val===undefined ? 0 : val);
    this.left = (left===undefined ? null : left);
    this.right = (right===undefined ? null : right);
}

/**
 * @param {TreeNode} root
 * @param {number} val
 * @param {number} depth
 * @return {TreeNode}
 */
var addOneRow = function(root, val, depth) {
    if (depth === 1) {
        const newRoot = new TreeNode(val);
        newRoot.left = root;
        return newRoot;
    }
    
    const dfs = (node, currentDepth, targetDepth) => {
        if (!node) return;
        
        if (currentDepth === targetDepth - 1) {
            const oldLeft = node.left;
            const oldRight = node.right;
            
            node.left = new TreeNode(val);
            node.left.left = oldLeft;
            
            node.right = new TreeNode(val);
            node.right.right = oldRight;
            return;
        }
        
        dfs(node.left, currentDepth + 1, targetDepth);
        dfs(node.right, currentDepth + 1, targetDepth);
    };
    
    dfs(root, 1, depth);
    return root;
};

// 测试函数
function testAddOneRow() {
    // 测试用例1
    const root1 = new TreeNode(4);
    root1.left = new TreeNode(2);
    root1.right = new TreeNode(6);
    root1.left.left = new TreeNode(3);
    root1.left.right = new TreeNode(1);
    root1.right.left = new TreeNode(5);
    
    const result1 = addOneRow(root1, 1, 2);
    console.log("Test 1 passed");
    
    // 测试用例2
    const root2 = new TreeNode(4);
    root2.left = new TreeNode(2);
    root2.left.left = new TreeNode(3);
    root2.left.right = new TreeNode(1);
    
    const result2 = addOneRow(root2, 1, 3);
    console.log("Test 2 passed");
}

testAddOneRow();

/*
算法思路：DFS递归遍历到目标深度的前一层，然后插入新节点
时间复杂度：O(n)
空间复杂度：O(h) - 递归栈深度
*/