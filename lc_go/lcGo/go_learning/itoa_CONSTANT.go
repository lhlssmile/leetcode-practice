/*
*
定义服务器规格常量
在云基础设施管理中，标准化服务器配置至关重要。本挑战将帮助你练习使用 Go 的 iota 常量生成器来创建一个清晰且高效的服务器规格配置系统。

任务
使用 iota 常量生成器定义服务器规格常量
为每个服务器规格常量分配内存容量
在 main() 函数中打印定义的服务器规格常量
要求
定义服务器规格常量：SMALL、MEDIUM、LARGE、XLARGE
使用 iota 生成递增值
分配内存容量：分别为 4GB、8GB、12GB、16GB
不要直接将具体的内存值分配给 MEDIUM、LARGE 和 XLARGE 常量
*/
package main

import "fmt"

// 定义服务器规格常量
const (
	SMALL ServerSpec = iota // 0 -> 4GB
	MEDIUM                  // 1 -> 8GB
	LARGE                   // 2 -> 12GB
	XLARGE                  // 3 -> 16GB
)

// ServerSpec 服务器规格类型
type ServerSpec int

// GetMemory 获取服务器规格对应的内存容量（GB）
func (s ServerSpec) GetMemory() int {
	return int(s)*4 + 4
}

// String 实现 Stringer 接口，用于打印
func (s ServerSpec) String() string {
	names := []string{"SMALL", "MEDIUM", "LARGE", "XLARGE"}
	if s >= 0 && int(s) < len(names) {
		return names[s]
	}
	return "UNKNOWN"
}

func main() {
	// 打印所有服务器规格常量及其内存容量
	fmt.Println("服务器规格配置：")
	fmt.Printf("%s: %dGB\n", SMALL, SMALL.GetMemory())
	fmt.Printf("%s: %dGB\n", MEDIUM, MEDIUM.GetMemory())
	fmt.Printf("%s: %dGB\n", LARGE, LARGE.GetMemory())
	fmt.Printf("%s: %dGB\n", XLARGE, XLARGE.GetMemory())

	// 演示 iota 的值
	fmt.Println("\niota 生成的值：")
	fmt.Printf("SMALL = %d\n", int(SMALL))
	fmt.Printf("MEDIUM = %d\n", int(MEDIUM))
	fmt.Printf("LARGE = %d\n", int(LARGE))
	fmt.Printf("XLARGE = %d\n", int(XLARGE))
}
