package main

import "fmt"

func longestCycle(edges []int) int {
	ans := -1
	visTime := make([]int, len(edges))
	curTime := 1
	for x := range edges {
		startTime := curTime
		for x != -1 && visTime[x] == 0 {
			visTime[x] = curTime
			curTime++
			x = edges[x]
		}
		if x != -1 && visTime[x] >= startTime {
			ans = max(ans, curTime-visTime[x])
		}
	}
	return ans
}

func main() {
	edges := []int{3, 3, 4, 2, 3}
	res := longestCycle(edges)
	fmt.Println(res)

}
