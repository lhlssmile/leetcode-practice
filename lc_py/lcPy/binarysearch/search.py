'''
整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。



示例 1：

输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
示例 2：

输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1
示例 3：

输入：nums = [1], target = 0
输出：-1


提示：

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
nums 中的每个值都 独一无二
题目数据保证 nums 在预先未知的某个下标上进行了旋转
-104 <= target <= 104
'''
from typing import List


class Solution:
    def search(self, nums: List[int], target: int) -> int:
        """
        旋转数组搜索 - 一次二分法（推荐解法）
        
        核心思路：
        旋转数组有个特点：至少有一半是有序的！
        [4,5,6,7,0,1,2] -> 左半部分[4,5,6,7]有序
        [6,7,0,1,2,4,5] -> 右半部分[2,4,5]有序
        
        算法步骤：
        1. 找到有序的那一半
        2. 判断target是否在有序部分的范围内
        3. 如果在，就在有序部分搜索；否则在另一半搜索
        """
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = (left + right) // 2
            
            # 找到目标值
            if nums[mid] == target:
                return mid
            
            # 判断哪一半是有序的
            if nums[left] <= nums[mid]:  # 左半部分有序
                # 判断target是否在左半部分的范围内
                if nums[left] <= target < nums[mid]:
                    right = mid - 1  # 在左半部分搜索
                else:
                    left = mid + 1   # 在右半部分搜索
            else:  # 右半部分有序
                # 判断target是否在右半部分的范围内
                if nums[mid] < target <= nums[right]:
                    left = mid + 1   # 在右半部分搜索
                else:
                    right = mid - 1  # 在左半部分搜索
        
        return -1
    
    def search_v2_find_pivot(self, nums: List[int], target: int) -> int:
        """
        方法二：先找旋转点，再二分搜索（你提到的思路）
        
        步骤：
        1. 找到旋转点（最小值的位置）
        2. 判断target在哪个有序部分
        3. 在对应部分进行标准二分搜索
        """
        def find_min_index():
            """找到最小值的索引（旋转点）"""
            left, right = 0, len(nums) - 1
            while left < right:
                mid = (left + right) // 2
                if nums[mid] > nums[right]:
                    left = mid + 1
                else:
                    right = mid
            return left
        
        def binary_search(left, right):
            """标准二分搜索"""
            while left <= right:
                mid = (left + right) // 2
                if nums[mid] == target:
                    return mid
                elif nums[mid] < target:
                    left = mid + 1
                else:
                    right = mid - 1
            return -1
        
        n = len(nums)
        if n == 1:
            return 0 if nums[0] == target else -1
        
        # 找到旋转点
        pivot = find_min_index()
        
        # 判断target在哪个部分
        if nums[pivot] <= target <= nums[n-1]:
            # target在右半部分 [pivot, n-1]
            return binary_search(pivot, n-1)
        else:
            # target在左半部分 [0, pivot-1]
            return binary_search(0, pivot-1)
    
    def search_v3_simple(self, nums: List[int], target: int) -> int:
        """
        方法三：最简单的理解方式（适合初学者）
        
        思路：
        1. 每次二分时，mid将数组分成两部分
        2. 至少有一部分是完全有序的
        3. 先判断target是否在有序部分，决定搜索方向
        """
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = left + (right - left) // 2
            
            if nums[mid] == target:
                return mid
            
            # 左半部分有序：nums[left] <= nums[mid]
            if nums[left] <= nums[mid]:
                # target在左半部分的有序范围内
                if nums[left] <= target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            # 右半部分有序：nums[mid] <= nums[right]
            else:
                # target在右半部分的有序范围内
                if nums[mid] < target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1
        
        return -1


def test_search():
    """
    测试函数 - 验证所有解法的正确性
    """
    solution = Solution()
    
    # 测试用例
    test_cases = [
        ([4,5,6,7,0,1,2], 0, 4),
        ([4,5,6,7,0,1,2], 3, -1),
        ([1], 0, -1),
        ([1], 1, 0),
        ([1,3], 3, 1),
        ([3,1], 1, 1),
        ([5,1,3], 3, 2),
    ]
    
    methods = [
        ("一次二分法", solution.search),
        ("先找旋转点", solution.search_v2_find_pivot),
        ("简单理解版", solution.search_v3_simple)
    ]
    
    for method_name, method in methods:
        print(f"\n=== {method_name} ===")
        all_passed = True
        
        for nums, target, expected in test_cases:
            result = method(nums, target)
            status = "✅" if result == expected else "❌"
            print(f"{status} nums={nums}, target={target} -> {result} (期望: {expected})")
            if result != expected:
                all_passed = False
        
        print(f"结果: {'全部通过' if all_passed else '存在错误'}")


def visualize_rotation():
    """
    可视化旋转数组的特点
    """
    print("\n🔄 旋转数组可视化分析")
    print("=" * 50)
    
    original = [0, 1, 2, 4, 5, 6, 7]
    rotations = [
        ([4, 5, 6, 7, 0, 1, 2], "在索引3处旋转"),
        ([6, 7, 0, 1, 2, 4, 5], "在索引2处旋转"),
        ([0, 1, 2, 4, 5, 6, 7], "在索引0处旋转(无旋转)")
    ]
    
    print(f"原数组: {original}")
    print()
    
    for rotated, desc in rotations:
        print(f"{desc}: {rotated}")
        
        # 分析有序部分
        n = len(rotated)
        for i in range(n):
            left_ordered = all(rotated[j] <= rotated[j+1] for j in range(i))
            right_ordered = all(rotated[j] <= rotated[j+1] for j in range(i, n-1))
            
            if left_ordered and right_ordered:
                print(f"  -> 在索引{i}分割: 左部分{rotated[:i+1]}有序, 右部分{rotated[i+1:]}有序")
                break
        print()


def explain_algorithm():
    """
    算法思路详细解释
    """
    print("\n📚 算法思路详解")
    print("=" * 50)
    
    print("""
🎯 核心洞察：
旋转数组的关键特性是：任意分割点，至少有一半是完全有序的！

🔍 算法步骤：
1. 取中点mid，将数组分为两部分
2. 判断哪一半是有序的（比较nums[left]和nums[mid]）
3. 检查target是否在有序部分的范围内
4. 根据判断结果，决定搜索左半部分还是右半部分

💡 判断技巧：
- 如果 nums[left] <= nums[mid]，说明左半部分有序
- 如果 nums[mid] <= nums[right]，说明右半部分有序
- 注意边界条件的处理

⏰ 时间复杂度：O(log n) - 每次都能排除一半元素
💾 空间复杂度：O(1) - 只用了常数个变量

🌟 为什么比"先找旋转点"的方法好？
- 只需要一次遍历，而不是两次
- 代码更简洁，逻辑更直接
- 常数因子更小，实际运行更快
    """)


if __name__ == "__main__":
    # 运行测试
    test_search()
    
    # 可视化分析
    visualize_rotation()
    
    # 算法解释
    explain_algorithm()
    
    print("\n🎉 学习完成！推荐使用第一种方法（一次二分法）")
    print("💡 关键是理解：旋转数组总有一半是有序的！")
