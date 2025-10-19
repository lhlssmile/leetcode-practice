package main

import (
	"bufio"
	"fmt"
	"math/bits"
	"os"
	"strconv"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)
var writer = bufio.NewWriter(os.Stdout)

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

func main() {
	defer writer.Flush()
	t, _ := strconv.Atoi(readLine())
	for ; t > 0; t-- {
		ab := readInts()
		a := ab[0]
		b := ab[1]

		clzA := bits.LeadingZeros32(uint32(a))
		clzB := bits.LeadingZeros32(uint32(b))

		if clzA > clzB {
			fmt.Fprintln(writer, -1)
		} else if a == b {
			fmt.Fprintln(writer, 0)
		} else {
			val := []int{}
			// 第一轮：填满a的0位
			for i := 0; i < 31; i++ {
				x := 1 << i
				if (a&x) == 0 && x <= a {
					a += x
					val = append(val, x)
				}
			}
			// 第二轮：翻转b的0位
			for i := 0; i < 31; i++ {
				x := 1 << i
				if (b&x) == 0 && x <= a {
					val = append(val, x)
				}
			}
			fmt.Fprintf(writer, "%d\n", len(val))
			for _, v := range val {
				fmt.Fprintf(writer, "%d ", v)
			}
			fmt.Fprintln(writer)
		}
	}
}
