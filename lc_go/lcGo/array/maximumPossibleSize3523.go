package main

import "fmt"

func maximumPossibleSize(nums []int) (ans int) {
	mx := 0
	for _, x := range nums {
		if x >= mx {
			mx = x
			ans++
		}
	}
	return
}

func main() {
	nums := []int{4, 2, 5, 3, 5}
	res := maximumPossibleSize(nums)
	fmt.Println(res)
}
