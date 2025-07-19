from typing import List

"""
【LeetCode 3202】找出有效子序列的最大长度 - 巧妙的二维DP解法

核心数学原理：
对于等式 (a+b) mod k = (b+c) mod k
根据模运算性质，可以移项得：(a+b-(b+c)) mod k = 0
化简得：(a-c) mod k = 0
这意味着 a 与 c 关于模 k 同余。

结论：有效子序列的偶数项都关于模k同余，奇数项都关于模k同余。

算法思路：
维护二维数组 f[y][x]，表示最后两项模k分别为y和x的子序列的最大长度。
对于当前元素 nums[i]，设 x = nums[i] % k，
可以在所有"最后两项为(x,y)"的子序列末尾添加当前元素，
得到"最后两项为(y,x)"的子序列，长度增加1。

状态转移：f[y][x] = f[x][y] + 1
"""


class Solution:
    def maximumLength(self, nums: List[int], k: int) -> int:
        """
        时间复杂度: O(n * k)
        空间复杂度: O(k^2)
        """
        # f[y][x] 表示最后两项模k分别为y和x的子序列的最大长度
        f = [[0] * k for _ in range(k)]
        
        for x in nums:
            x %= k  # 当前元素模k的值
            
            # 遍历所有可能的前一个元素的模k值y
            for y, fxy in enumerate(f[x]):
                # 在"最后两项为(x,y)"的子序列末尾添加当前元素x
                # 得到"最后两项为(y,x)"的子序列，长度+1
                f[y][x] = fxy + 1
        
        return max(map(max, f))



def detailed_example():
    """
    详细例子演示：nums = [1, 2, 1, 2, 1, 2], k = 3
    """
    print("=== 详细例子演示 ===")
    print("nums = [1, 2, 1, 2, 1, 2], k = 3")
    print("目标：找最长有效子序列（相邻元素和模3相同）")
    print()
    
    # 手动模拟算法过程
    nums = [1, 2, 1, 2, 1, 2]
    k = 2
    f = [[0] * k for _ in range(k)]
    
    print("初始状态：f = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]")
    print("f[y][x] 表示最后两项模k分别为y和x的子序列最大长度")
    print()
    
    for i, num in enumerate(nums):
        x = num % k
        print(f"第{i+1}步：处理元素 {num}，x = {num} % {k} = {x}")
        
        old_f = [row[:] for row in f]  # 保存旧状态
        
        for y in range(k):
            if f[x][y] > 0:  # 只显示有意义的更新
                f[y][x] = f[x][y] + 1
                print(f"  更新 f[{y}][{x}] = f[{x}][{y}] + 1 = {f[x][y]} + 1 = {f[y][x]}")
                print(f"  含义：在末尾为({x},{y})的子序列后加{x}，得到末尾为({y},{x})的子序列")
        
        # 处理单个元素的情况
        for y in range(k):
            if old_f[x][y] == 0:
                f[y][x] = max(f[y][x], 1)
        
        print(f"  当前f矩阵：")
        for row_idx, row in enumerate(f):
            print(f"    f[{row_idx}] = {row}")
        print(f"  当前最大长度：{max(map(max, f))}")
        print()
    
    print(f"最终答案：{max(map(max, f))}")
    print()


def step_by_step_analysis():
    """
    逐步分析算法的核心思想
    """
    print("=== 算法核心思想分析 ===")
    print()
    
    print("1. 数学原理推导：")
    print("   有效子序列：相邻元素和模k相同")
    print("   即：(a+b) mod k = (b+c) mod k")
    print("   移项：(a+b-(b+c)) mod k = 0")
    print("   化简：(a-c) mod k = 0")
    print("   结论：a ≡ c (mod k)")
    print()
    
    print("2. 关键洞察：")
    print("   - 有效子序列的偶数位置元素模k同余")
    print("   - 有效子序列的奇数位置元素模k同余")
    print("   - 子序列形如：[a, b, a, b, a, b, ...] (模k意义下)")
    print()
    
    print("3. 状态设计：")
    print("   f[y][x] = 最后两项模k分别为y和x的子序列最大长度")
    print("   当遇到新元素x时，可以接在所有末尾为(x,y)的子序列后")
    print("   形成新的末尾为(y,x)的子序列")
    print()
    
    print("4. 状态转移：")
    print("   f[y][x] = f[x][y] + 1")
    print("   含义：在末尾为(x,y)的子序列后添加x，得到末尾为(y,x)的子序列")
    print()
    
    print("5. 为什么这样设计巧妙？")
    print("   - 避免了复杂的子序列枚举")
    print("   - 利用了有效子序列的周期性特点")
    print("   - 状态转移简洁高效")
    print("   - 自动处理了所有可能的有效模式")
    print()


def compare_with_naive_approach():
    """
    与朴素方法的对比
    """
    print("=== 与朴素方法对比 ===")
    print()
    
    print("朴素方法（我之前教的）：")
    print("- 枚举所有可能的余数模式")
    print("- 对每种模式单独计算最长长度")
    print("- 时间复杂度：O(n * k)")
    print("- 空间复杂度：O(k)")
    print("- 思路直观但需要分类讨论")
    print()
    
    print("巧妙方法（当前这种）：")
    print("- 统一处理所有模式")
    print("- 利用状态转移自动维护")
    print("- 时间复杂度：O(n * k)")
    print("- 空间复杂度：O(k²)")
    print("- 思路巧妙，代码简洁")
    print()
    
    print("总结：")
    print("- 两种方法时间复杂度相同")
    print("- 巧妙方法空间稍大但思路更优雅")
    print("- 巧妙方法体现了DP状态设计的艺术")
    print()


if __name__ == '__main__':
    # 详细演示
    detailed_example()
    step_by_step_analysis()
    compare_with_naive_approach()
    
    print("=== 测试用例 ===")
    solution = Solution()

    # 示例1
    nums1 = [1, 2, 3, 4, 5]
    k1 = 2
    print(f"示例1: nums={nums1}, k={k1}")
    print(f"结果: {solution.maximumLength(nums1, k1)}")
    print()

    # 示例2
    nums2 = [1, 4, 2, 3, 1, 4]
    k2 = 3
    print(f"示例2: nums={nums2}, k={k2}")
    print(f"结果: {solution.maximumLength(nums2, k2)}")
    print()
    
    # 示例3：演示用例
    nums3 = [1, 2, 1, 2, 1, 2]
    k3 = 3
    print(f"示例3: nums={nums3}, k={k3}")
    print(f"结果: {solution.maximumLength(nums3, k3)}")