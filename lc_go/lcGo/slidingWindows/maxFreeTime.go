package main

func maxFreeTime(eventTime, k int, startTime, endTime []int) (ans int) {
	//左startTime 右eventTime
	n := len(startTime)
	freeTime := make([]int, n+1)

	freeTime[0] = startTime[0] - 0

	for i := 1; i < n; i++ {
		freeTime[i] = startTime[i] - endTime[i-1]
	}
	freeTime[n] = eventTime - endTime[n-1]

	s := 0

	for i, f := range freeTime {
		s += f
		if i < k {
			continue
		}
		ans = max(ans, s)

		s -= freeTime[i-k]
	}
	return
}

func main() {
	eventTime := 5
	k := 1
	startTime := []int{1, 3}
	endTime := []int{2, 5}

	maxFreeTime(eventTime, k, startTime, endTime)

}
