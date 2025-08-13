package main

func maximumsSplicedArray(nums1 []int, nums2 []int) int {
	var dfs func(a, b []int) int
	n := len(nums1)
	dfs = func(a, b []int) int {
		curr, best := 0, 0
		for i := 0; i < n; i++ {
			curr = max(b[i]-a[i], curr+b[i]-a[i])
			best = max(best, curr)
		}

		return best
	}
	s1, s2 := 0, 0
	for _, x := range nums1 {
		s1 += x
	}
	for _, x := range nums2 {
		s2 += x
	}
	return max(s1+dfs(nums1, nums2), s2+dfs(nums2, nums1))
}

func main() {
	nums1 := []int{60, 60, 60}
	nums2 := []int{10, 90, 10}
	maximumsSplicedArray(nums1, nums2)
}
