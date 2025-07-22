'''
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。



示例 1:



输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10
示例 2：



输入： heights = [2,4]
输出： 4


提示：

1 <= heights.length <=105
0 <= heights[i] <= 104
'''
from typing import List


class Solution:
    # 方法1：单调栈解法 (推荐) - O(n) 时间复杂度
    def largestRectangleArea(self, heights: List[int]) -> int:
        """
        🎯 核心思想：单调递增栈
        
        对于每个柱子，我们要找到：
        1. 左边第一个比它矮的柱子位置 (left_bound)
        2. 右边第一个比它矮的柱子位置 (right_bound)
        
        然后以当前柱子为高度的最大矩形宽度就是：
        width = right_bound - left_bound - 1
        面积 = height * width
        """
        stack = []  # 单调递增栈，存储索引
        max_area = 0
        
        # 在数组末尾添加一个高度为0的柱子，确保所有柱子都能被处理
        heights = heights + [0]
        
        for i, h in enumerate(heights):
            # 当前高度小于栈顶高度时，说明找到了栈顶柱子的右边界
            while stack and h < heights[stack[-1]]:
                # 弹出栈顶，计算以该柱子为高度的最大矩形面积
                height = heights[stack.pop()]
                
                # 计算宽度：右边界是当前位置i，左边界是新栈顶的下一个位置
                width = i if not stack else i - stack[-1] - 1
                
                # 更新最大面积
                max_area = max(max_area, height * width)
            
            # 将当前索引入栈
            stack.append(i)
        
        return max_area
    
    # 方法2：暴力解法 (用于理解问题) - O(n²) 时间复杂度
    def largestRectangleArea_Brute(self, heights: List[int]) -> int:
        """
        暴力解法：对每个位置，向左右扩展找到最大矩形
        """
        max_area = 0
        n = len(heights)
        
        for i in range(n):
            # 以 heights[i] 为高度，向左右扩展
            left = i
            right = i
            
            # 向左扩展
            while left > 0 and heights[left - 1] >= heights[i]:
                left -= 1
            
            # 向右扩展
            while right < n - 1 and heights[right + 1] >= heights[i]:
                right += 1
            
            # 计算面积
            width = right - left + 1
            area = heights[i] * width
            max_area = max(max_area, area)
        
        return max_area
    
    # 方法3：分治解法 (了解即可) - O(n log n) 平均时间复杂度
    def largestRectangleArea_DivideConquer(self, heights: List[int]) -> int:
        """
        分治思想：最大矩形要么跨越中点，要么完全在左半部分，要么完全在右半部分
        """
        def divide_conquer(left: int, right: int) -> int:
            if left > right:
                return 0
            
            # 找到最小高度的位置
            min_idx = left
            for i in range(left, right + 1):
                if heights[i] < heights[min_idx]:
                    min_idx = i
            
            # 跨越中点的矩形面积
            cross_area = heights[min_idx] * (right - left + 1)
            
            # 左半部分的最大面积
            left_area = divide_conquer(left, min_idx - 1)
            
            # 右半部分的最大面积
            right_area = divide_conquer(min_idx + 1, right)
            
            return max(cross_area, left_area, right_area)
        
        return divide_conquer(0, len(heights) - 1)


# 📚 单调栈学习笔记
"""
🎯 单调栈核心思想：

1. 什么是单调栈？
   - 栈内元素保持单调性（递增或递减）
   - 当新元素破坏单调性时，弹出栈顶元素

2. 为什么用单调栈？
   - 可以在 O(n) 时间内找到每个元素的"下一个更大/更小元素"
   - 本题中：找到每个柱子左右两边第一个更矮的柱子

3. 算法步骤详解：
   
   以 heights = [2,1,5,6,2,3] 为例：
   
   i=0, h=2: stack=[] → stack=[0]
   i=1, h=1: h < heights[0]=2
     - 弹出0，计算面积：height=2, width=1, area=2
     - stack=[1]
   i=2, h=5: stack=[1,2]
   i=3, h=6: stack=[1,2,3]
   i=4, h=2: h < heights[3]=6
     - 弹出3，计算面积：height=6, width=1, area=6
     - h < heights[2]=5
     - 弹出2，计算面积：height=5, width=2, area=10 ← 最大！
     - stack=[1,4]
   i=5, h=3: stack=[1,4,5]
   i=6, h=0: 依次弹出所有元素计算面积

4. 关键理解：
   - 栈中存储的是索引，不是高度值
   - 当弹出栈顶时，说明找到了该柱子的右边界
   - 新栈顶的下一个位置就是左边界
   - 添加哨兵0确保所有柱子都能被处理

5. 时间复杂度分析：
   - 每个元素最多入栈一次，出栈一次
   - 总时间复杂度：O(n)
   - 空间复杂度：O(n)
"""


# 🧪 测试函数
def test_largest_rectangle():
    solution = Solution()
    
    test_cases = [
        ([2,1,5,6,2,3], 10),
        ([2,4], 4),
        ([1], 1),
        ([1,1], 2),
        ([2,1,2], 3),
        ([0,2,0], 2),
        ([5,4,3,2,1], 9)  # 递减序列
    ]
    
    print("=== 柱状图最大矩形面积测试 ===")
    
    for heights, expected in test_cases:
        print(f"\n测试: {heights} (期望: {expected})")
        
        # 测试单调栈解法
        result1 = solution.largestRectangleArea(heights.copy())
        print(f"  单调栈解法: {result1}")
        
        # 测试暴力解法
        result2 = solution.largestRectangleArea_DivideConquer(heights.copy())
        print(f"  暴力解法:   {result2}")
        
        # 验证结果
        if result1 == result2 == expected:
            print(f"  ✅ 所有方法结果一致且正确")
        else:
            print(f"  ❌ 结果不一致或错误")


# 🎨 可视化单调栈过程
def visualize_stack_process(heights: List[int]):
    print(f"\n=== 单调栈过程可视化: {heights} ===")
    
    stack = []
    max_area = 0
    heights_with_sentinel = heights + [0]
    
    for i, h in enumerate(heights_with_sentinel):
        print(f"\n步骤 {i+1}: 处理高度 {h} (索引 {i})")
        print(f"  当前栈: {stack}")
        
        while stack and h < heights_with_sentinel[stack[-1]]:
            height_idx = stack.pop()
            height = heights_with_sentinel[height_idx]
            width = i if not stack else i - stack[-1] - 1
            area = height * width
            max_area = max(max_area, area)
            
            print(f"    弹出索引 {height_idx} (高度 {height})")
            print(f"    计算面积: 高度={height}, 宽度={width}, 面积={area}")
            print(f"    当前最大面积: {max_area}")
        
        if i < len(heights):  # 不添加哨兵到栈中
            stack.append(i)
            print(f"  入栈索引 {i}, 栈变为: {stack}")
    
    print(f"\n最终结果: {max_area}")
    return max_area


if __name__ == "__main__":
    test_largest_rectangle()
    
    # 可视化一个例子
    print("\n" + "="*50)
    visualize_stack_process([2,1,5,6,2,3])



