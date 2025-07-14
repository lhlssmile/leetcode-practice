package main

import "fmt"

func decodeEmoji(codePoint rune) rune {
	return codePoint
}

func printEmoji(codePoint rune, description string) {
	emoji := decodeEmoji(codePoint)
	fmt.Printf("Unicode码点:0x%x -> 表情符号: %c (%s)\n", codePoint, emoji, description)
}

func main() {

	var (
		grinning rune = 0x1F600
	)
	sparking := rune(0x1F496)
	printEmoji(grinning, "咧嘴笑")
	printEmoji(sparking, "hh")
}
