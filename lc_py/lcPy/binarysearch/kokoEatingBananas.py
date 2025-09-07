# LeetCode 875: 爱吃香蕉的珂珂
# 珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。
# 警卫已经离开了，将在 h 小时后回来。
# 珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。
# 每个小时，她将会选择一堆香蕉，从中吃掉 k 根。
# 如果这堆香蕉少于 k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。
# 珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
# 返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

from typing import List
import math

def min_eating_speed_binary_search(piles: List[int], h: int) -> int:
    """二分查找解法"""
    if not piles:
        return 0
    
    left, right = 1, max(piles)  # 二分范围
    while left < right:
        mid = left + (right - left) // 2  # 中点
        total_hours = 0
        for pile in piles:
            total_hours += (pile + mid - 1) // mid  # ceil(pile / mid)
        
        if total_hours <= h:  # 可行，试更小
            right = mid
        else:  # 不可行，需更大
            left = mid + 1
    
    return left  # 最小 k

def min_eating_speed_math_ceil(piles: List[int], h: int) -> int:
    """使用math.ceil的二分查找解法"""
    if not piles:
        return 0
    
    left, right = 1, max(piles)
    while left < right:
        mid = left + (right - left) // 2
        total_hours = sum(math.ceil(pile / mid) for pile in piles)
        
        if total_hours <= h:
            right = mid
        else:
            left = mid + 1
    
    return left

def min_eating_speed_optimized(piles: List[int], h: int) -> int:
    """优化的二分查找解法"""
    if not piles:
        return 0
    
    # 优化：如果时间充足，最小速度可能是1
    # 如果时间紧张，最小速度接近平均值
    total_bananas = sum(piles)
    left = math.ceil(total_bananas / h)
    right = max(piles)
    
    while left < right:
        mid = left + (right - left) // 2
        total_hours = sum((pile + mid - 1) // mid for pile in piles)
        
        if total_hours <= h:
            right = mid
        else:
            left = mid + 1
    
    return left

def min_eating_speed_brute_force(piles: List[int], h: int) -> int:
    """暴力解法（用于验证）"""
    if not piles:
        return 0
    
    for k in range(1, max(piles) + 1):
        total_hours = sum((pile + k - 1) // k for pile in piles)
        if total_hours <= h:
            return k
    
    return max(piles)

def min_eating_speed_functional(piles: List[int], h: int) -> int:
    """函数式编程风格"""
    if not piles:
        return 0
    
    def can_finish(k: int) -> bool:
        return sum((pile + k - 1) // k for pile in piles) <= h
    
    left, right = 1, max(piles)
    
    # 使用递归的二分查找
    def binary_search(left: int, right: int) -> int:
        if left >= right:
            return left
        
        mid = left + (right - left) // 2
        if can_finish(mid):
            return binary_search(left, mid)
        else:
            return binary_search(mid + 1, right)
    
    return binary_search(left, right)

def main():
    test_cases = [
        ([3, 6, 7, 11], 8),
        ([30, 11, 23, 4, 20], 5),
        ([30, 11, 23, 4, 20], 6),
        ([1, 1, 1, 1], 4),
        ([312884470], 312884469)
    ]
    
    print("=== 爱吃香蕉的珂珂 ===")
    
    for i, (piles, h) in enumerate(test_cases, 1):
        print(f"\n测试用例 {i}: piles={piles}, h={h}")
        
        result1 = min_eating_speed_binary_search(piles, h)
        result2 = min_eating_speed_math_ceil(piles, h)
        result3 = min_eating_speed_optimized(piles, h)
        result4 = min_eating_speed_functional(piles, h)
        
        print(f"二分查找: {result1}")
        print(f"math.ceil版本: {result2}")
        print(f"优化版本: {result3}")
        print(f"函数式版本: {result4}")
        
        # 对于小数据集验证暴力解法
        if len(piles) <= 10 and max(piles) <= 100:
            result5 = min_eating_speed_brute_force(piles, h)
            print(f"暴力解法: {result5}")
            assert result1 == result5, "结果不一致!"
        
        # 验证结果一致性
        assert result1 == result2 == result3 == result4, "结果不一致!"
        
        # 验证解的正确性
        total_hours = sum((pile + result1 - 1) // result1 for pile in piles)
        assert total_hours <= h, f"解不正确: 需要{total_hours}小时，但只有{h}小时"
        
        if result1 > 1:
            # 验证这是最小解
            total_hours_slower = sum((pile + result1 - 2) // (result1 - 1) for pile in piles)
            assert total_hours_slower > h, f"不是最小解: 速度{result1-1}也可以在{total_hours_slower}小时内完成"

if __name__ == "__main__":
    main()