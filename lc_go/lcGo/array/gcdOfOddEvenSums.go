package main

func gcdOfOddEvenSums(n int) int {

	return gcd(n*n, n*(n+1))
}

func gcd(a, b int) int {
	if b == 0 {
		if a < 0 {
			return -a
		}
		return a
	}
	return gcd(b, a%b)
}
func main() {

}
