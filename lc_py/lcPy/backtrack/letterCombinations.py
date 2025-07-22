'''

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。





示例 1：

输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
示例 2：

输入：digits = ""
输出：[]
示例 3：

输入：digits = "2"
输出：["a","b","c"]


提示：

0 <= digits.length <= 4
digits[i] 是范围 ['2', '9'] 的一个数字。
'''
from typing import List


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:

        dict_map = {'2': 'abc', '3': 'def', '4': 'ghi',
                    '5': 'jkl', '6': 'mno', '7': 'pqrs',
                    '8': 'tuv', '9': 'wxyz'}
        ans = []
        if len(digits) == 0:
            return []
        
        path = []  # 当前路径
        
        def backtrack(idx: int) -> None:
            # 退出条件：已经处理完所有数字
            if idx == len(digits):
                ans.append(''.join(path))
                return
            
            # 获取当前数字对应的字母
            current_digit = digits[idx]
            letters = dict_map[current_digit]
            
            # 遍历当前数字对应的所有字母（笛卡尔积的核心）
            for letter in letters:
                # 选择：将字母加入路径
                path.append(letter)
                
                # 递归：处理下一个数字
                backtrack(idx + 1)
                
                # 回滚：撤销选择，恢复状态
                path.pop()
        
        backtrack(0)
        return ans
    
    # 方法2：迭代解法（用于对比）
    def letterCombinations_iterative(self, digits: str) -> List[str]:
        if not digits:
            return []
        
        dict_map = {'2': 'abc', '3': 'def', '4': 'ghi',
                    '5': 'jkl', '6': 'mno', '7': 'pqrs',
                    '8': 'tuv', '9': 'wxyz'}
        
        result = [""]
        for digit in digits:
            letters = dict_map[digit]
            result = [combo + letter for combo in result for letter in letters]
        
        return result
    
    # 调试版本：带详细输出的回溯
    def letterCombinations_debug(self, digits: str) -> List[str]:
        if not digits:
            return []
        
        dict_map = {'2': 'abc', '3': 'def', '4': 'ghi',
                    '5': 'jkl', '6': 'mno', '7': 'pqrs',
                    '8': 'tuv', '9': 'wxyz'}
        ans = []
        path = []
        
        def backtrack(idx: int, depth: int = 0) -> None:
            indent = "  " * depth
            print(f"{indent}进入 backtrack(idx={idx}), 当前路径: {path}")
            
            # 退出条件
            if idx == len(digits):
                result = ''.join(path)
                ans.append(result)
                print(f"{indent}✅ 找到一个组合: '{result}'")
                return
            
            current_digit = digits[idx]
            letters = dict_map[current_digit]
            print(f"{indent}处理数字 '{current_digit}', 对应字母: '{letters}'")
            
            for i, letter in enumerate(letters):
                print(f"{indent}选择字母 '{letter}' ({i+1}/{len(letters)})")
                
                # 选择
                path.append(letter)
                print(f"{indent}路径更新: {path}")
                
                # 递归
                backtrack(idx + 1, depth + 1)
                
                # 回滚
                removed = path.pop()
                print(f"{indent}回滚: 移除 '{removed}', 路径恢复: {path}")
        
        print("=== 开始回溯调试 ===")
        backtrack(0)
        print(f"=== 调试结束，共找到 {len(ans)} 个组合 ===")
        return ans


# 测试函数
def test_letter_combinations():
    solution = Solution()
    
    print("\n=== 电话号码的字母组合测试 ===\n")
    
    # 测试用例1
    print("测试用例1: digits = '23'")
    result1 = solution.letterCombinations("23")
    print(f"回溯算法结果: {result1}")
    print(f"结果数量: {len(result1)}")
    
    result1_iter = solution.letterCombinations_iterative("23")
    print(f"迭代算法结果: {result1_iter}")
    print(f"两种方法结果一致: {sorted(result1) == sorted(result1_iter)}")
    
    print("\n" + "-" * 50 + "\n")
    
    # 测试用例2
    print("测试用例2: digits = ''")
    result2 = solution.letterCombinations("")
    print(f"空字符串结果: {result2}")
    
    print("\n" + "-" * 50 + "\n")
    
    # 测试用例3
    print("测试用例3: digits = '2'")
    result3 = solution.letterCombinations("2")
    print(f"单个数字结果: {result3}")
    
    print("\n" + "-" * 50 + "\n")
    
    # 调试版本演示
    print("调试版本演示: digits = '23'")
    solution.letterCombinations_debug("23")
    
    print("\n=== 回溯算法核心思想 ===")
    print("1. 选择：从当前数字对应的字母中选择一个")
    print("2. 递归：处理下一个数字")
    print("3. 回滚：撤销当前选择，尝试其他可能")
    print("4. 剪枝：当处理完所有数字时，记录结果")
    
    print("\n时间复杂度: O(3^m × 4^n)，其中m是对应3个字母的数字个数，n是对应4个字母的数字个数")
    print("空间复杂度: O(3^m × 4^n)，用于存储所有组合")


if __name__ == "__main__":
    test_letter_combinations()