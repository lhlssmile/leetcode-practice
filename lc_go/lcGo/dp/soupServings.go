package main

func soupServings(n int) float64 {
	if n >= 5000 {
		return 1.0
	}
	memo := make(map[int]map[int]float64)
	operations := [][]int{{100, 0}, {75, 25}, {50, 50}, {25, 75}}

	var dfs func(int, int) float64
	dfs = func(a, b int) float64 {
		if a <= 0 && b <= 0 {
			return 0.5
		}
		if a <= 0 {
			return 1.0
		}
		if b <= 0 {
			return 0.0
		}

		if _, ok := memo[a]; ok {
			if val, ok2 := memo[a][b]; ok2 {
				return val
			}
		}

		prob := 0.0
		for _, op := range operations {
			newA := a - op[0]
			newB := b - op[1]
			prob += 0.25 * dfs(newA, newB)
		}
		if memo[a] == nil {
			memo[a] = make(map[int]float64)
		}
		memo[a][b] = prob
		return prob
	}

	return dfs(n, n)
}

func main() {

}
