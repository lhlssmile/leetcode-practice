package main

func minOperations(nums []int) int {
	inc, dbl := 0, 0
	bitLen := 0
	for _, x := range nums {
		bitLen = 0
		for x > 0 {

			if x&1 != 0 {
				inc++
			}
			x >>= 1
			bitLen++
			dbl = max(dbl, bitLen)
		}
	}
	return inc + max(dbl-1, 0)
}

func main() {

}
