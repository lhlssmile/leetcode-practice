package main

func nextGreaterElement(nums1, nums2 []int) []int {
	ans := make([]int, len(nums1))
	idx := make(map[int]int, len(nums1))
	for i, x := range nums1 {
		idx[x] = i
	}
	for i, _ := range ans {
		ans[i] = -1
	}

	st := make([]int, len(nums2))

	for _, x := range nums2 {
		for len(st) > 0 && x > st[len(st)-1] {
			ans[idx[st[len(st)-1]]] = x
			st = st[:len(st)-1]
		}
		if _, ok := idx[x]; ok {
			st = append(st, x)
		}
	}
	return ans
}

func main() {

}
