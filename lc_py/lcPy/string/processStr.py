'''
给你一个字符串 s，它由小写英文字母和特殊字符：*、# 和 % 组成。

请根据以下规则从左到右处理 s 中的字符，构造一个新的字符串 result：

如果字符是 小写 英文字母，则将其添加到 result 中。
字符 '*' 会 删除 result 中的最后一个字符（如果存在）。
字符 '#' 会 复制 当前的 result 并 追加 到其自身后面。
字符 '%' 会 反转 当前的 result。
在处理完 s 中的所有字符后，返回最终的字符串 result。©leetcode

'''

class Solution:
    def processStr(self, s: str) -> str:
        result = ""
        
        for symbol in s:
            if symbol.islower():  # 小写英文字母
                result += symbol
            elif symbol == '*':  # 删除最后一个字符
                if result:  # 如果result不为空
                    result = result[:-1]  # 删除最后一个字符
            elif symbol == '#':  # 复制当前result并追加
                result += result  # 将result复制一份追加到自身
            elif symbol == '%':  # 反转当前result
                result = result[::-1]  # 使用切片反转字符串
        
        return result