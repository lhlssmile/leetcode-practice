# 力扣第3301题：高度互不相同的最大塔高和

from typing import List
import sys


class Solution:
    def maximum_total_sum(self, maximum_height: List[int]) -> int:
        """
        计算高度互不相同的最大塔高和
        
        算法思路：
        1. 将高度数组按降序排序
        2. 从最高的塔开始，确保每个塔的高度严格小于前一个塔
        3. 如果无法满足条件，返回-1
        4. 否则，返回所有调整后高度的总和
        
        Args:
            maximum_height: 塔的高度数组
            
        Returns:
            高度互不相同的最大塔高和，如果无法满足条件则返回-1
        """
        # 创建副本并按降序排序
        heights = sorted(maximum_height, reverse=True)
        
        prev = sys.maxsize
        ans = 0
        
        for h in heights:
            # 确保当前高度严格小于前一个高度
            curr = min(h, prev - 1)
            if curr <= 0:
                return -1
            ans += curr
            prev = curr
        
        return ans


def test_maximum_total_sum():
    """
    测试函数
    """
    solution = Solution()
    
    # 定义测试用例
    test_cases = [
        {
            'name': '基本测试1',
            'heights': [5, 3, 4, 1, 1],
            'expected': 13
        },
        {
            'name': '基本测试2',
            'heights': [6, 5, 3, 9, 2, 7],
            'expected': 29
        },
        {
            'name': '基本测试3',
            'heights': [3, 2, 1],
            'expected': 6
        },
        {
            'name': '无法满足条件',
            'heights': [1, 1, 1],
            'expected': -1
        }
    ]
    
    # 运行测试并输出结果
    for tc in test_cases:
        result = solution.maximum_total_sum(tc['heights'])
        status = '通过' if result == tc['expected'] else '失败'
        print(f"测试 {tc['name']}: 结果 = {result}, 预期 = {tc['expected']}, {status}")


if __name__ == "__main__":
    test_maximum_total_sum()