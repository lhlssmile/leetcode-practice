/*
*
解码 Unicode 表情符号
在全球通信中，将 Unicode 码点（code points）转换为可读的表情符号（emoji）对于跨平台消息应用程序至关重要。你的任务是实现一个 Go 程序，将特定的 Unicode 码点转换为对应的表情符号字符。

任务
在 ~/project 目录下创建一个名为 emoji_decoder.go 的 Go 程序
实现一个函数，将特定的 Unicode 码点（0x1F600、0x1F496、0x1F648）转换为表情符号字符
使用正确的 rune 类型将解码后的表情符号打印到控制台
要求
使用 rune 类型表示 Unicode 字符

至少将三个不同的 Unicode 码点转换为表情符号
使用 fmt.Printf() 和 %c 格式说明符打印表情符号
程序必须能够编译并运行，且不出现错误
*/
package main

import "fmt"

// decodeEmoji 将Unicode码点转换为表情符号字符
func decodeEmoji(codePoint rune) rune {
	return codePoint
}

// printEmoji 打印表情符号及其信息
func printEmoji(codePoint rune, description string) {
	emoji := decodeEmoji(codePoint)
	fmt.Printf("Unicode码点: 0x%X -> 表情符号: %c (%s)\n", codePoint, emoji, description)
}

func main() {
	fmt.Println("=== Unicode 表情符号解码器 ===")
	fmt.Println()

	// 定义要解码的Unicode码点
	var (
		grinning  rune = 0x1F600 // 😀 咧嘴笑脸
		sparkling rune = 0x1F496 // 💖 闪闪发光的心
		monkey    rune = 0x1F648 // 🙈 非礼勿视猴子

	)

	// 打印每个表情符号
	printEmoji(grinning, "咧嘴笑脸")
	printEmoji(sparkling, "闪闪发光的心")
	printEmoji(monkey, "非礼勿视猴子")

	fmt.Println()
	fmt.Println("=== 直接使用rune类型演示 ===")

	// 直接使用rune类型创建表情符号
	emojis := []rune{0x1F600, 0x1F496, 0x1F648}
	descriptions := []string{"笑脸", "爱心", "猴子"}

	for i, emoji := range emojis {
		fmt.Printf("%s: %c\n", descriptions[i], emoji)
	}

	fmt.Println()
	fmt.Println("=== 更多表情符号示例 ===")

	// 额外的表情符号示例
	moreEmojis := map[rune]string{
		0x1F44D: "👍 点赞",
		0x1F389: "🎉 庆祝",
		0x1F525: "🔥 火焰",
		0x2764:  "❤️ 红心",
		0x1F680: "🚀 火箭",
	}

	for codePoint, desc := range moreEmojis {
		fmt.Printf("0x%X -> %c %s\n", codePoint, codePoint, desc)
	}

	fmt.Println()
	fmt.Println("=== rune类型特性演示 ===")

	// 演示rune的特性
	r := rune(0x1F600)
	fmt.Printf("rune值: %d\n", r)
	fmt.Printf("十六进制: 0x%X\n", r)
	fmt.Printf("字符: %c\n", r)
	fmt.Printf("字符串: %s\n", string(r))
}
