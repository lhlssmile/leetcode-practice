package main

func minSwaps(nums []int) (ans int) {
	n := len(nums)
	k := 0
	for _, x := range nums {
		k += x
	}
	if k == 0 || k == n {
		return 0
	}
	s := 0
	for i := n - k; i < n-1; i++ {
		s += nums[i]
	}
	max_s := s
	for i := 0; i < n; i++ {
		s += nums[(i+n-1)%n]
		max_s = max(max_s, s)
		s -= nums[(i-k+n)%n]
	}
	return k - max_s
}

func main() {

}
