package main

import "fmt"

func minCosts(cost []int) []int {
    for i:= 1;i < len(cost);i++ {
        cost[i] = min(cost[i - 1],cost[i])
    }
    return cost
}
func main(){
	cost := []int{5,3,1,2,4}
	res := minCosts(cost)
	fmt.Println(res)
}