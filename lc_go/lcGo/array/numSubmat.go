package main

func numSubmat(mat [][]int) (ans int) {
	m, n := len(mat), len(mat[0])

	for top := 0; top < m; top++ {
		a := make([]int, n)
		for bottom := top; bottom < m; bottom++ {
			h := bottom - top + 1
			last := -1
			for j := 0; j < n; j++ {
				a[j] += mat[bottom][j]
				if a[j] != h {
					last = j
				} else {
					ans += j - last
				}
			}
		}

	}
	return
}

func main() {

}
