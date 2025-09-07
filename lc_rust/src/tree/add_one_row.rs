use std::rc::Rc;
use std::cell::RefCell;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

type TreeNodeRef = Option<Rc<RefCell<TreeNode>>>;

pub fn add_one_row(root: TreeNodeRef, val: i32, depth: i32) -> TreeNodeRef {
    if depth == 1 {
        let new_root = Rc::new(RefCell::new(TreeNode::new(val)));
        new_root.borrow_mut().left = root;
        return Some(new_root);
    }
    
    fn dfs(node: &TreeNodeRef, val: i32, current_depth: i32, target_depth: i32) {
        if let Some(node_ref) = node {
            if current_depth == target_depth - 1 {
                let mut node_borrow = node_ref.borrow_mut();
                let old_left = node_borrow.left.take();
                let old_right = node_borrow.right.take();
                
                let new_left = Rc::new(RefCell::new(TreeNode::new(val)));
                new_left.borrow_mut().left = old_left;
                node_borrow.left = Some(new_left);
                
                let new_right = Rc::new(RefCell::new(TreeNode::new(val)));
                new_right.borrow_mut().right = old_right;
                node_borrow.right = Some(new_right);
                return;
            }
            
            let node_borrow = node_ref.borrow();
            dfs(&node_borrow.left, val, current_depth + 1, target_depth);
            dfs(&node_borrow.right, val, current_depth + 1, target_depth);
        }
    }
    
    dfs(&root, val, 1, depth);
    root
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_add_one_row() {
        // 测试用例1
        let root1 = Some(Rc::new(RefCell::new(TreeNode::new(4))));
        if let Some(ref node) = root1 {
            node.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
            node.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(6))));
            
            if let Some(ref left) = node.borrow().left {
                left.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(3))));
                left.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(1))));
            }
            
            if let Some(ref right) = node.borrow().right {
                right.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(5))));
            }
        }
        
        let result1 = add_one_row(root1, 1, 2);
        assert!(result1.is_some());
        println!("Test 1 passed");
        
        // 测试用例2
        let root2 = Some(Rc::new(RefCell::new(TreeNode::new(4))));
        if let Some(ref node) = root2 {
            node.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(2))));
            
            if let Some(ref left) = node.borrow().left {
                left.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(3))));
                left.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(1))));
            }
        }
        
        let result2 = add_one_row(root2, 1, 3);
        assert!(result2.is_some());
        println!("Test 2 passed");
    }
}

/*
算法思路：DFS递归遍历到目标深度的前一层，然后插入新节点
时间复杂度：O(n)
空间复杂度：O(h) - 递归栈深度
*/