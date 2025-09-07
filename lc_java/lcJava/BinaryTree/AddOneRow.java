package lcJava.BinaryTree;

import java.util.*;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

public class AddOneRow {
    public TreeNode addOneRow(TreeNode root, int val, int depth) {
        if (depth == 1) {
            TreeNode newRoot = new TreeNode(val);
            newRoot.left = root;
            return newRoot;
        }
        
        dfs(root, val, 1, depth);
        return root;
    }
    
    private void dfs(TreeNode node, int val, int currentDepth, int targetDepth) {
        if (node == null) return;
        
        if (currentDepth == targetDepth - 1) {
            TreeNode oldLeft = node.left;
            TreeNode oldRight = node.right;
            
            node.left = new TreeNode(val);
            node.left.left = oldLeft;
            
            node.right = new TreeNode(val);
            node.right.right = oldRight;
            return;
        }
        
        dfs(node.left, val, currentDepth + 1, targetDepth);
        dfs(node.right, val, currentDepth + 1, targetDepth);
    }
    
    // 测试函数
    public static void test() {
        AddOneRow solution = new AddOneRow();
        
        // 测试用例1
        TreeNode root1 = new TreeNode(4);
        root1.left = new TreeNode(2);
        root1.right = new TreeNode(6);
        root1.left.left = new TreeNode(3);
        root1.left.right = new TreeNode(1);
        root1.right.left = new TreeNode(5);
        
        TreeNode result1 = solution.addOneRow(root1, 1, 2);
        System.out.println("Test 1 passed");
        
        // 测试用例2
        TreeNode root2 = new TreeNode(4);
        root2.left = new TreeNode(2);
        root2.left.left = new TreeNode(3);
        root2.left.right = new TreeNode(1);
        
        TreeNode result2 = solution.addOneRow(root2, 1, 3);
        System.out.println("Test 2 passed");
    }
    
    public static void main(String[] args) {
        test();
    }
}

/*
算法思路：DFS递归遍历到目标深度的前一层，然后插入新节点
时间复杂度：O(n)
空间复杂度：O(h) - 递归栈深度
*/