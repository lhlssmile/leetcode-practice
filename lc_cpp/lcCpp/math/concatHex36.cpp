/**
* 给你一个整数 n。

返回 n2 的 十六进制表示 和 n3 的 三十六进制表示 拼接成的字符串。

十六进制 数定义为使用数字 0 – 9 和大写字母 A - F 表示 0 到 15 的值。

三十六进制 数定义为使用数字 0 – 9 和大写字母 A - Z 表示 0 到 35 的值。

  

示例 1：

输入：n = 13

输出： "A91P1"

解释：

n2 = 13 * 13 = 169。在十六进制中，它转换为 (10 * 16) + 9 = 169，对应于 "A9"。
n3 = 13 * 13 * 13 = 2197。在三十六进制中，它转换为 (1 * 362) + (25 * 36) + 1 = 2197，对应于 "1P1"。
连接两个结果得到 "A9" + "1P1" = "A91P1"。
示例 2：

输入：n = 36

输出："5101000"

解释：

n2 = 36 * 36 = 1296。在十六进制中，它转换为 (5 * 162) + (1 * 16) + 0 = 1296，对应于 "510"。
n3 = 36 * 36 * 36 = 46656。在三十六进制中，它转换为 (1 * 363) + (0 * 362) + (0 * 36) + 0 = 46656，对应于 "1000"。
连接两个结果得到 "510" + "1000" = "5101000"。©leetcode
*/
#include <string>
#include <iostream>
//
// Created by 24276 on 2025/7/5.
//
class concat_hex36 {
public:
    std::string concatHex36(int n) {
        int square_n = n * n;
        int cube_n = n * n * n;
        
        // 将n²转换为十六进制
        std::string hex16 = toBase(square_n, 16);
        
        // 将n³转换为三十六进制
        std::string hex36 = toBase(cube_n, 36);
        
        return hex16 + hex36;
    }
    
private:
    // 通用进制转换函数，使用取余的方式
    std::string toBase(int num, int base) {
        if (num == 0) return "0";
        
        std::string result = "";
        while (num > 0) {
            int remainder = num % base;
            if (remainder < 10) {
                result = char('0' + remainder) + result;
            } else {
                result = char('A' + remainder - 10) + result;
            }
            num /= base;
        }
        return result;
    }
};

int main() {
    concat_hex36 solution;
    
    // 测试示例1: n = 13
    int n1 = 13;
    std::string res1 = solution.concatHex36(n1);
    std::cout << "n = " << n1 << ", result = " << res1 << std::endl;
    std::cout << "Expected: A91P1" << std::endl;
    
    // 测试示例2: n = 36
    int n2 = 36;
    std::string res2 = solution.concatHex36(n2);
    std::cout << "n = " << n2 << ", result = " << res2 << std::endl;
    std::cout << "Expected: 5101000" << std::endl;
    
    // 验证计算过程
    std::cout << "\n验证 n = 13:" << std::endl;
    std::cout << "n² = 13² = " << 13*13 << " -> 十六进制: " << solution.concatHex36(13).substr(0, 2) << std::endl;
    std::cout << "n³ = 13³ = " << 13*13*13 << " -> 三十六进制: " << solution.concatHex36(13).substr(2) << std::endl;
    
    return 0;
}
