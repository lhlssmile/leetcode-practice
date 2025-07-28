package main

func countMaxOrSubsets(nums []int) (ans int) {
	n := len(nums)
	totalOr := 0
	for _, x := range nums {
		totalOr |= x
	}
	var dfs func(int, int)

	dfs = func(idx, currentSubsets int) {
		if idx == n {
			if currentSubsets == totalOr {
				ans++
			}
			return
		}
		dfs(idx+1, currentSubsets)
		dfs(idx+1, currentSubsets|nums[idx])
	}
	dfs(0, 0)
	return
}

func main() {

}
