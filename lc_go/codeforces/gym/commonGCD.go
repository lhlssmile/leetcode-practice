package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strconv"
	"strings"
)

var (
	reader = bufio.NewReader(os.Stdin)
	writer = bufio.NewWriter(os.Stdout)
)

func readLine() string {
	s, _ := reader.ReadString('\n')
	return strings.TrimSpace(s)
}

func readInts() []int {
	fields := strings.Fields(readLine())
	res := make([]int, len(fields))
	for i, f := range fields {
		res[i], _ = strconv.Atoi(f)
	}
	return res
}

func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	defer writer.Flush()

	// 读取 n
	line := readLine()
	if line == "" {
		return
	}
	n, _ := strconv.Atoi(line)

	// 读取 n 个整数（可能一行也可能多行）
	a := []int{}
	for len(a) < n {
		nums := readInts()
		a = append(a, nums...)
	}

	// 计算所有数的 gcd
	g := a[0]
	for _, x := range a {
		g = gcd(g, x)
	}

	for i := range a {
		a[i] /= g
	}

	M := slices.Max(a)
	primeFactor := make([]int, M+1)
	for i := 2; i <= M; i++ {
		if primeFactor[i] == 0 {
			for j := i; j <= M; j += i {
				if primeFactor[j] == 0 {
					primeFactor[j] = i
				}
			}
		}
	}

	vis := make([]bool, M+1)
	for _, x0 := range a {
		x := x0
		for x > 1 {
			p := primeFactor[x]
			if vis[p] {
				fmt.Fprintln(writer, "NO")
				return
			}
			vis[p] = true
			for x%p == 0 {
				x /= p
			}
		}
	}

	fmt.Fprintln(writer, "YES")
}
