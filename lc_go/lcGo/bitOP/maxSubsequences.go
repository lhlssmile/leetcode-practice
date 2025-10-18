package main

func maxSubsequences(nums []int) int {
	b := make([]int, 32)
	for _, x := range nums {
		for i := 31; i >= 0; i-- {
			if (x>>i)&1 == 0 {
				continue
			}
			if b[i] == 0 {
				b[i] = x
				break
			}
			x ^= b[i]
		}

	}
	ans := 0
	for i := 31; i >= 0; i-- {
		if (ans^b[i]) > ans && b[i] != 0 {
			ans ^= b[i]
		}
	}
	return ans
}
func main() {

}
