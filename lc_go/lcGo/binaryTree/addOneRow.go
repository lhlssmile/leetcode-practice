package main

import "fmt"

type TreeNode struct {
    Val   int
    Left  *TreeNode
    Right *TreeNode
}

func addOneRow(root *TreeNode, val int, depth int) *TreeNode {
    if depth == 1 {
        newRoot := &TreeNode{Val: val}
        newRoot.Left = root
        return newRoot
    }
    
    var dfs func(*TreeNode, int, int, int)
    dfs = func(node *TreeNode, val, currentDepth, targetDepth int) {
        if node == nil {
            return
        }
        
        if currentDepth == targetDepth-1 {
            oldLeft := node.Left
            oldRight := node.Right
            
            node.Left = &TreeNode{Val: val}
            node.Left.Left = oldLeft
            
            node.Right = &TreeNode{Val: val}
            node.Right.Right = oldRight
            return
        }
        
        dfs(node.Left, val, currentDepth+1, targetDepth)
        dfs(node.Right, val, currentDepth+1, targetDepth)
    }
    
    dfs(root, val, 1, depth)
    return root
}

// 测试函数
func testAddOneRow() {
    // 测试用例1
    root1 := &TreeNode{Val: 4}
    root1.Left = &TreeNode{Val: 2}
    root1.Right = &TreeNode{Val: 6}
    root1.Left.Left = &TreeNode{Val: 3}
    root1.Left.Right = &TreeNode{Val: 1}
    root1.Right.Left = &TreeNode{Val: 5}
    
    result1 := addOneRow(root1, 1, 2)
    fmt.Println("Test 1 passed", result1 != nil)
    
    // 测试用例2
    root2 := &TreeNode{Val: 4}
    root2.Left = &TreeNode{Val: 2}
    root2.Left.Left = &TreeNode{Val: 3}
    root2.Left.Right = &TreeNode{Val: 1}
    
    result2 := addOneRow(root2, 1, 3)
    fmt.Println("Test 2 passed", result2 != nil)
}

func main() {
    testAddOneRow()
}

/*
算法思路：DFS递归遍历到目标深度的前一层，然后插入新节点
时间复杂度：O(n)
空间复杂度：O(h) - 递归栈深度
*/