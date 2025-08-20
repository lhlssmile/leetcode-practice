package main

func change(amount int, coins []int) int {
	f := make([]int, amount+1)
	f[0] = 1

	for _, x := range coins {
		for c := x; c <= amount; c++ {
			f[c] += f[c-x]
		}
	}

	return f[amount]
}

func main() {

}
