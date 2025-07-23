package main

func partition(s string) [][]string {
	ans := make([][]string, 256)
	for i := range ans {
		ans[i] = make([]string, len(s))
		for j := range ans[i] {
			ans[i][j] = ""
		}
	}
	var dfs func()
	dfs = func() {

	}
	dfs()
	return ans
}

func main() {

}
