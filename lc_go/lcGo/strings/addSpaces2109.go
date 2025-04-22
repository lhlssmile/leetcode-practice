package main

import "fmt"

func addSpaces(s string, spaces []int) string {
	n, k := len(s), len(spaces)

	result := make([]byte, n+k)
	copy(result[:n], s)
	oldIndex, newIndex, spaceIndex := n-1, n+k-1, k-1

	for oldIndex >= 0 {
		result[newIndex] = result[oldIndex]
		newIndex--
		if spaceIndex >= 0 && spaces[spaceIndex] == oldIndex {
			result[newIndex] = ' '
			newIndex--
			spaceIndex--
		}
		oldIndex--
	}
	return string(result)
}

func addSpacesUSEDB(s string, spaces []int) string {
	ans := make([]byte, 0, len(s)+len(spaces))
	j := 0
	for i, c := range s {
		if j < len(spaces) && spaces[j] == i {
			ans = append(ans, ' ')
			j++
		}
		ans = append(ans, byte(c))
	}
	return string(ans)

}

func main() {
	spaces := []int{8, 13, 15}
	s := "LeetcodeHelpsMeLearn"
	ans1 := addSpaces(s, spaces)
	fmt.Println(ans1)
	ans := addSpacesUSEDB(s, spaces)
	fmt.Println(ans)
}
