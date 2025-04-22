package main

import (
	"fmt"
	"math"
)

func numRabbits(answers []int) (allRabbits int) {
	freq := make(map[int]int)
	for _, answer := range answers {
		freq[answer]++
	}
	for x, k := range freq {
		grouSize := x + 1
		group := int(math.Ceil(float64(k) / float64(grouSize)))
		allRabbits += group * grouSize
	}
	return
}

func main() {
	answers := []int{1, 1, 2}
	res := numRabbits(answers)
	fmt.Println(res)
}
