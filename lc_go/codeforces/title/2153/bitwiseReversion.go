package main

import (
	"bufio"
	"fmt"
	"os"
)

func ok(x, y, z int) bool {
	for i := 0; i < 30; i++ {
		xi := (x >> i) & 1
		yi := (y >> i) & 1
		zi := (z >> i) & 1
		if xi+yi+zi == 2 {
			return false // 两个1一个0 不可能
		}
	}
	return true
}

func main() {
	in := bufio.NewReader(os.Stdin)
	var t int
	fmt.Fscan(in, &t)
	for ; t > 0; t-- {
		var x, y, z int
		fmt.Fscan(in, &x, &y, &z)
		if ok(x, y, z) {
			fmt.Println("YES")
		} else {
			fmt.Println("NO")
		}
	}
}
