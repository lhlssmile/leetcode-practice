/**
 * Alice 和 Bob 正在玩一个游戏。最初，Alice 有一个字符串 word = "a"。

给定一个正整数 k。

现在 Bob 会要求 Alice 执行以下操作 无限次 :

将 word 中的每个字符 更改 为英文字母表中的 下一个 字符来生成一个新字符串，并将其 追加 到原始的 word。
例如，对 "c" 进行操作生成 "cd"，对 "zb" 进行操作生成 "zbac"。

在执行足够多的操作后， word 中 至少 存在 k 个字符，此时返回 word 中第 k 个字符的值。

注意，在操作中字符 'z' 可以变成 'a'。

 

示例 1:

输入：k = 5

输出："b"

解释：

最初，word = "a"。需要进行三次操作:

生成的字符串是 "b"，word 变为 "ab"。
生成的字符串是 "bc"，word 变为 "abbc"。
生成的字符串是 "bccd"，word 变为 "abbcbccd"。
示例 2:

输入：k = 10

输出："c"
 * 
 */

#include <iostream>
//
// Created by 24276 on 2025/7/3.
//
class kth_character3304 {
public:
    char kthCharacter(int k) {
        // 'a' -> 'ab' -> 'abbc' -> 'abbc bccd' -> 'abbcbccd bccdcdde'
        /**
         * 你的理解很棒！确实是等比数列! 从0开始 2^0,2^1,.....2^n。能直接算出来转为子问题!
         * 
         * 你的思路基本正确，但需要完善：
         * ex k = 5: 4(2^2) < 5 <= 8(2^3), 5 - 4 = 1 (这个1是在右半部分的位置)
         * 右半部分是左半部分每个字符+1得到的，所以递归求解位置1，然后+1
         * 
         * ex2 k = 10: 8(2^3) < 10 <= 16(2^4), 10 - 8 = 2
         * 递归求解位置2，得到'b'，然后+1得到'c'
         * 
         * 关键洞察：每次操作后，字符串长度翻倍！
         * 新的右半部分 = 左半部分的每个字符+1
         */
        if (k == 1) return 'a';
        
        // 找到最大的2的幂次，使得2^i < k
        int power = 1;
        while (power * 2 < k) {
            power *= 2;
        }
        
        // k在右半部分，递归求解左半部分对应位置，然后字符+1
        char leftChar = kthCharacter(k - power);
        return (leftChar == 'z') ? 'a' : leftChar + 1;
    }
};

int main() {
    kth_character3304 ps;
    
    // 测试用例1: k = 5, 期望输出 'b'
    std::cout << "k=5: " << ps.kthCharacter(5) << std::endl;
    
    // 测试用例2: k = 10, 期望输出 'c' 
    std::cout << "k=10: " << ps.kthCharacter(10) << std::endl;
    
    // 额外测试用例
    std::cout << "k=1: " << ps.kthCharacter(1) << std::endl;   // 'a'
    std::cout << "k=2: " << ps.kthCharacter(2) << std::endl;   // 'b'
    std::cout << "k=3: " << ps.kthCharacter(3) << std::endl;   // 'b'
    std::cout << "k=4: " << ps.kthCharacter(4) << std::endl;   // 'c'
    
    // 演示字符串生成过程
    std::cout << "\n字符串生成过程演示:" << std::endl;
    std::cout << "第0次: a" << std::endl;
    std::cout << "第1次: ab" << std::endl; 
    std::cout << "第2次: abbc" << std::endl;
    std::cout << "第3次: abbcbccd" << std::endl;
    std::cout << "位置:  12345678..." << std::endl;
    
    return 0;
}
