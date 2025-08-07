package main

type Union struct {
	parent []int
	count  int
}

func BuildUnionFind(n int) *Union {
	parent := make([]int, n)
	for i := range parent {
		parent[i] = i
	}
	return &Union{parent: parent, count: n}
}

func (u *Union) unionSet(x, y int) {
	rootX := u.find(x)
	rootY := u.find(y)

	if rootX != rootY {
		u.parent[rootX] = rootY
		u.count--
	}
}

func (u *Union) getCount() int {
	return u.count
}

func (u *Union) find(x int) int {
	if u.parent[x] != x {
		u.parent[x] = u.find(u.parent[x])
	}
	return u.parent[x]
}

func findCircleNum(isConnected [][]int) int {
	n := len(isConnected)

	u := BuildUnionFind(n)

	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			if isConnected[i][j] == 1 {
				u.unionSet(i, j)
			}
		}
	}
	return u.getCount()
}

func main() {

}
