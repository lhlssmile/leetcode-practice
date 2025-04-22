package main

import "fmt"

func maxArea(height []int) (ans int) {
	l, r := 0, len(height)-1
	for l < r {
		h := height[l]
		if height[r] < h {
			h = height[r]
		}
		area := h * (r - l)
		if area > ans {
			ans = area
		}
		if height[l] < height[r] {
			l++
		} else {
			r--
		}
	}
	return
}

func main() {
	height := []int{1, 8, 6, 2, 5, 4, 8, 3, 7}
	result := maxArea(height)
	fmt.Println(result)

}
