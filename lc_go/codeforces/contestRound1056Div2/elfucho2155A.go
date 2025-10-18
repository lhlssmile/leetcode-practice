package contestRound1056Div2

import "fmt"

func main() {
	var t int
	fmt.Scan(&t)
	for ; t > 0; t-- {
		var n int
		fmt.Scan(&n)
		fmt.Println(n*2 - 2)
	}

}
