package main

import "fmt"

type TreeNode struct {
	val   int
	left  *TreeNode
	right *TreeNode
}
type Pair struct {
	depth int
	node  *TreeNode
}

func lcaDeepestLeaves(root *TreeNode) *TreeNode {
	_, node := helper(root)
	return node
}
func helper(node *TreeNode) (int, *TreeNode) {
	if node == nil {
		return -1, nil
	}
	if node.left == nil && node.right == nil {
		return 0, node
	}

	leftDepth, leftLca := helper(node.left)
	rightDepth, rightLca := helper(node.right)
	if leftDepth == rightDepth {
		return leftDepth + 1, node
	} else if leftDepth > rightDepth {
		return leftDepth + 1, leftLca
	} else {
		return rightDepth + 1, rightLca
	}
}

func createTree(values []interface{}) *TreeNode {
	if len(values) == 0 || values[0] == nil {
		return nil
	}
	//第一个node当根
	root := &TreeNode{val: values[0].(int)}
	//初始化队列
	queue := []*TreeNode{root}
	index := 1
	for len(queue) > 0 && index < len(values) {
		current := queue[0]
		queue = queue[1:]
		if index < len(values) && values[index] != nil {
			current.left = &TreeNode{val: values[index].(int)}
			queue = append(queue, current.left)
		}
		index++
		if index < len(values) && values[index] != nil {
			current.right = &TreeNode{val: values[index].(int)}
			queue = append(queue, current.right)
		}
		index++
	}
	return root
}

func main() {
	values := []interface{}{3, 5, 1, 6, 2, 0, 8, nil, nil, 7, 4}
	tree := createTree(values)
	res := lcaDeepestLeaves(tree)
	fmt.Println(res.val)
}
