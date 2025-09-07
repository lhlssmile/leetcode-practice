def canThreePartsEqualSum(arr):
    total_sum = 0
    for v in arr:
        total_sum += v
    
    if total_sum % 3 != 0:
        return False
    
    part = 0
    current_sum = 0
    
    for x in arr:
        current_sum += x
        if current_sum == total_sum // 3:
            current_sum = 0
            part += 1
    
    return part >= 3

class Solution:
    def canThreePartsEqualSum(self, arr):
        return canThreePartsEqualSum(arr)

def test_can_three_parts_equal_sum():
    solution = Solution()
    
    print("=== LeetCode 1013: 将数组分成和相等的三个部分 ===")
    
    # 测试用例1
    arr1 = [0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1]
    result1 = solution.canThreePartsEqualSum(arr1)
    print(f"测试用例1: {arr1} -> 结果: {result1}")
    
    # 测试用例2
    arr2 = [0, 2, 1, -6, 6, 6, 7, 9, -1, 2, 0, 1]
    result2 = solution.canThreePartsEqualSum(arr2)
    print(f"测试用例2: {arr2} -> 结果: {result2}")
    
    # 测试用例3
    arr3 = [3, 3, 3]
    result3 = solution.canThreePartsEqualSum(arr3)
    print(f"测试用例3: {arr3} -> 结果: {result3}")
    
    # 测试用例4
    arr4 = [1, 1, 1, 1]
    result4 = solution.canThreePartsEqualSum(arr4)
    print(f"测试用例4: {arr4} -> 结果: {result4}")
    
    # 测试用例5
    arr5 = [0, 0, 0, 0]
    result5 = solution.canThreePartsEqualSum(arr5)
    print(f"测试用例5: {arr5} -> 结果: {result5}")

if __name__ == "__main__":
    test_can_three_parts_equal_sum()

"""
算法说明:
1. 首先计算数组总和，如果不能被3整除则返回False
2. 遍历数组，累加当前和
3. 当累加和等于目标值(sum//3)时，重置累加和并增加部分计数
4. 最终检查是否找到至少3个部分

时间复杂度: O(n)
空间复杂度: O(1)

Python特性:
1. 动态类型
2. 列表推导式
3. 简洁语法
4. 内置数据结构
"""