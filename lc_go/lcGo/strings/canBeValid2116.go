package main

import "fmt"

func canBeValid(s string, locked string) bool {
	if len(s)%2 != 0 {
		return false
	}
	mn, mx := 0, 0
	for i, lock := range locked {
		if lock == '1' { // 不能改
			// ( ascii 40 ) 41	取模的结果 * 2 ex 若为 ( d = 1,若为) 1 - 2 = -1
			d := 1 - int(s[i]%2*2) // 左括号是 1，右括号是 -1
			mx += d
			if mx < 0 { // c 不能为负
				return false
			}
			mn += d
		} else { // 可以改
			mx++ // 改成左括号，c 加一
			mn-- // 改成右括号，c 减一
		}
		if mn < 0 { // c 不能为负
			mn = 1 // 此时 c 的取值范围都是奇数，最小的奇数是 1
		}
	}
	return mn == 0 // 说明最终 c 能是 0
}

func main() {
	s := "()()"
	locked := "0000"
	res := canBeValid(s, locked)
	fmt.Println(res)

}
