package main

func canEat(candiesCount []int, queries [][]int) []bool {
	n := len(candiesCount)

	prefix := make([]int, n+1)

	for i := 0; i < n; i++ {
		prefix[i+1] = prefix[i] + candiesCount[i]
	}
	ans := make([]bool, len(queries))

	for i := 0; i < len(queries); i++ {
		CandyType := queries[i][0]
		favoriteDay := queries[i][1]
		dailyCapacity := queries[i][2]
		minTaking := favoriteDay + 1
		maxTaking := minTaking * dailyCapacity
		currCandy := prefix[CandyType] + 1
		nxtCandy := prefix[CandyType+1]
		ans[i] = !(maxTaking < currCandy || minTaking > nxtCandy)
	}
	return ans
}

func main() {

}
