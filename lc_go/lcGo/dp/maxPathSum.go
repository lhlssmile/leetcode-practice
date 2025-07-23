package main

/*
Go语言匿名函数的下划线写法详解：

1. 下划线 _ 的含义：
   var _ func(node *TreeNode) int  // _ 表示"空白标识符"，占位用
   _ = func(node *TreeNode) int {  // 把函数赋值给 _（丢弃）
       // 但这样无法调用！因为 _ 不是变量名
   }

2. := 和 var _ 的区别：
   // ❌ 短变量声明（无法递归）
   dfs := func(node *TreeNode) int {
       dfs(node.Left)  // 编译错误！dfs还未定义
   }
   
   // ✅ 正确的下划线用法（可以递归）
   var dfs func(node *TreeNode) int  // 先声明类型
   dfs = func(node *TreeNode) int {  // 再赋值（不用下划线！）
       return dfs(node.Left)  // 可以递归调用
   }

3. 为什么GoLand建议用var而不是:=？
   因为递归函数需要在定义时就能"看到"自己的名字！
   
4. 下划线的真正用途：
   _ = someValue  // 丢弃不需要的返回值
   for _, v := range slice {}  // 丢弃索引，只要值
*/

type TreeNode struct {
	Val         int
	Left, Right *TreeNode
}

func maxPathSum(root *TreeNode) (sum int) {
	sum = -1001 // 题目约束：节点值范围[-1000, 1000]
	
	// GoLand建议的匿名函数定义方式
	var dfs func(node *TreeNode) int
	dfs = func(node *TreeNode) int {
		if node == nil {
			return 0
		}
		
		// 递归计算左右子树的最大贡献值（负数时取0）
		leftMax := max(0, dfs(node.Left))
		rightMax := max(0, dfs(node.Right))
		
		// 更新全局最大路径和（经过当前节点的路径）
		currentMax := node.Val + leftMax + rightMax
		sum = max(sum, currentMax)
		
		// 返回当前节点能向上贡献的最大值
		return node.Val + max(leftMax, rightMax)
	}
	
	// 调用匿名函数
	dfs(root)
	return sum
}

// Go 1.21之前需要自定义max函数
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func main() {
	// 测试用例：[1,2,3]
	//     1
	//    / \
	//   2   3
	root := &TreeNode{
		Val: 1,
		Left: &TreeNode{Val: 2},
		Right: &TreeNode{Val: 3},
	}
	
	result := maxPathSum(root)
	println("最大路径和:", result) // 应该输出 6 (2->1->3)
	
	// 测试用例：[-10,9,20,null,null,15,7]
	//      -10
	//      / \
	//     9  20
	//       /  \
	//      15   7
	root2 := &TreeNode{
		Val: -10,
		Left: &TreeNode{Val: 9},
		Right: &TreeNode{
			Val: 20,
			Left: &TreeNode{Val: 15},
			Right: &TreeNode{Val: 7},
		},
	}
	
	result2 := maxPathSum(root2)
	println("最大路径和:", result2) // 应该输出 42 (15->20->7)
}
