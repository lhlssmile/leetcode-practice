#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
LeetCode Python 快速开始模板
使用方法:
1. 复制这个模板到新文件
2. 修改类名和函数名
3. 实现算法逻辑
4. 在main函数中添加测试用例
5. 按 Ctrl+F5 运行或点击右上角运行按钮
"""

from typing import List, Optional, Dict, Set, Tuple
import sys
from collections import defaultdict, deque, Counter
import heapq
import bisect

class Solution:
    def sampleProblem(self, nums: List[int]) -> int:
        """
        示例问题：找到数组中的最大值
        
        Args:
            nums: 输入数组
            
        Returns:
            数组中的最大值
        """
        if not nums:
            return 0
            
        max_val = nums[0]
        for num in nums[1:]:
            if num > max_val:
                max_val = num
                
        return max_val

def test_solution():
    """测试函数"""
    solution = Solution()
    
    # 测试用例1
    test1 = [1, 3, 2, 5, 4]
    result1 = solution.sampleProblem(test1)
    print(f"测试1: 输入={test1}, 输出={result1}, 期望=5")
    assert result1 == 5, f"测试1失败: 期望5, 得到{result1}"
    
    # 测试用例2
    test2 = [-1, -3, -2]
    result2 = solution.sampleProblem(test2)
    print(f"测试2: 输入={test2}, 输出={result2}, 期望=-1")
    assert result2 == -1, f"测试2失败: 期望-1, 得到{result2}"
    
    # 测试用例3
    test3 = []
    result3 = solution.sampleProblem(test3)
    print(f"测试3: 输入={test3}, 输出={result3}, 期望=0")
    assert result3 == 0, f"测试3失败: 期望0, 得到{result3}"
    
    print("\n✅ 所有测试通过!")

def main():
    """主函数"""
    print("🐍 Python LeetCode 快速开始模板")
    print("=" * 40)
    
    try:
        test_solution()
    except AssertionError as e:
        print(f"❌ 测试失败: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"❌ 运行错误: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()