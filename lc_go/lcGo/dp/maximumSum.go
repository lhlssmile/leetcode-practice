package main

import "math"

func maximumSum(arr []int) int {
	ans, f1, f2 := arr[0], arr[0], math.MinInt16
	n := len(arr)
	for i := 1; i < n; i++ {
		v := arr[i]
		newf1 := max(v, v+f1)
		newf2 := max(f1, f2+v)

		f1, f2 = newf1, newf2
		ans = max(ans, max(f1, f2))
	}
	return ans
}

func main() {

}
