package main

func nextGreaterElements(nums []int) []int {
	n := len(nums)
	ans := make([]int, len(nums))

	for i := range nums {
		ans[i] = -1
	}

	var st []int

	for i := 2*n - 1; i >= 0; i-- {
		cur := nums[i%n]
		for len(st) > 0 && nums[st[len(st)-1]] <= cur {
			st = st[:len(st)-1]
		}
		if i < n {
			if len(st) > 0 {
				ans[i] = nums[st[len(st)-1]]
			}
		}
		st = append(st, i%n)
	}
	return ans
}

func main() {
	nums := []int{1, 2, 1}
	nextGreaterElements(nums)
}
