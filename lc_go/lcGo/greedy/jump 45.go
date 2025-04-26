package main

import "fmt"

func jump(nums []int) (step int) {
	n := len(nums)
	end, maxPos := 0,0
	for i := range nums[:n - 1] {
		maxPos = max(maxPos,i + nums[i])
		if i == end {
			end = maxPos 
			step++
		}
	}
	return 
}
func main(){
	nums := []int{2,3,1,1,4}
	fmt.Println(jump(nums))
}