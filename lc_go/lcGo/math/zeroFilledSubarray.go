package main

func zeroFilledSubarray(nums []int) int64 {
	ans, cnt := 0, 0

	for _, x := range nums {
		if x == 0 {
			cnt++
			ans += cnt
		} else {
			cnt = 0
		}
	}
	return int64(ans)
}

func main() {

}
