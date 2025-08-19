package main

func quickDigitSum(a int) int {
	return a % 9
}

func smallestIndex(nums []int) int {

	for i, x := range nums {
		if i == quickDigitSum(x) {
			return i
		}
	}
	return -1
}

func main() {
	nums := []int{243}
	println(smallestIndex(nums))
}
