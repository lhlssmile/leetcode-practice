package main

func maxAbsoluteSum(nums []int) int {
	miEn, miSum, mxSum, mxEn := 0, 0, 0, 0

	for _, x := range nums {
		mxEn = max(x, x+mxEn)
		mxSum = max(mxEn, mxSum)
		miEn = min(x, x+miEn)
		miSum = min(miSum, miEn)
	}
	return max(mxSum, -miSum)
}
func main() {
	nums := []int{2, -5, 1, -4, 3, -2}
	println(maxAbsoluteSum(nums))
}
