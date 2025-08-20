package main

func permute(nums []int) [][]int {
	ans := [][]int{}
	res := []int{}
	n := len(nums)
	vis := make([]bool, n)
	for i := range vis {
		vis[i] = false
	}
	var dfs func(i int)
	dfs = func(i int) {
		if i == n {
			tmp := make([]int, len(res))
			copy(tmp, res)
			ans = append(ans, tmp)
			return
		}

		for j := 0; j < n; j++ {
			if !vis[j] {
				res = append(res, nums[j])
				vis[j] = true
				dfs(i + 1)
				res = res[:len(res)-1]
				vis[j] = false
			}
		}
	}
	dfs(0)
	return ans
}

func main() {

}
