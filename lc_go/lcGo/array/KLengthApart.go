package main

func kLengthApart(nums []int, k int) bool {
	// n := len(nums)
	last := -1

	for i, x := range nums {
		if x == 1 {
			if last != -1 && i-last <= k {
				return false
			}
			last = i
		}
	}
	return true
}

func main() {

}
