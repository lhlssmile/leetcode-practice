package main

func numberOfPoints(nums [][]int) (ans int) {
	maxEnd := 0
	for _, interval := range nums {
		maxEnd = max(maxEnd, interval[1])
	}

	diff := make([]int, maxEnd+2) // 注意下面有 end+1
	for _, interval := range nums {
		diff[interval[0]]++
		diff[interval[1]+1]--
	}

	s := 0
	for _, d := range diff {
		s += d
		if s > 0 {
			ans++
		}
	}
	return
}

func main() {
	nums := [][]int{
		{3, 6}, {1, 5}, {4, 7},
	}
	numberOfPoints(nums)
}
