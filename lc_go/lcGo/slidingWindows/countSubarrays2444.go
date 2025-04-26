package main

import "fmt"

func countSubarrays(nums []int,minK,maxK int)(ans int64){
	n := len(nums)

	left,minKPos,maxKPos := -1,-1,-1

	for i := range nums[:n] {
		if nums[i] < minK || nums[i] > maxK {
			left = i
		}
		if nums[i] == minK {
			minKPos = i
		}
		if nums[i] == maxK {
			maxKPos = i 
		}
		validStart := min(minKPos,maxKPos)
		if validStart > left {
			ans += int64(validStart - left)
		}

	}
	return 
}

func main(){
	nums := []int{1,3,5,2,7,5}
	minK,maxK := 1,5
	res := countSubarrays(nums,minK,maxK)
	fmt.Println(res)
}