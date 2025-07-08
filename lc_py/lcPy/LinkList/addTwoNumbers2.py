'''
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.
示例 2：

输入：l1 = [0], l2 = [0]
输出：[0]
示例 3：

输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
'''

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        """
        使用指针遍历两个链表，保存进位，直接修改l1作为结果链表
        时间复杂度: O(max(m,n))，空间复杂度: O(1)
        """
        carry = 0  # 进位
        current = l1  # 当前节点指针
        prev = None   # 保存前一个节点，用于处理l1比l2短的情况
        
        # 同时遍历两个链表
        while l1 or l2 or carry:
            # 获取当前位的值
            val1 = l1.val if l1 else 0
            val2 = l2.val if l2 else 0
            
            # 计算当前位的和
            total = val1 + val2 + carry
            carry = total // 10  # 新的进位
            digit = total % 10   # 当前位的数字
            
            # 如果l1还有节点，直接修改其值
            if l1:
                l1.val = digit
                prev = l1
                l1 = l1.next
            else:
                # l1已经结束，但还有l2或进位，需要创建新节点
                prev.next = ListNode(digit)
                prev = prev.next
            
            # 移动l2指针
            if l2:
                l2 = l2.next
        
        return current

# 测试用例
def create_linked_list(arr):
    """根据数组创建链表"""
    if not arr:
        return None
    head = ListNode(arr[0])
    current = head
    for i in range(1, len(arr)):
        current.next = ListNode(arr[i])
        current = current.next
    return head

def print_linked_list(head):
    """打印链表"""
    result = []
    current = head
    while current:
        result.append(current.val)
        current = current.next
    return result

# 测试
if __name__ == "__main__":
    solution = Solution()
    
    # 测试用例1: [2,4,3] + [5,6,4] = [7,0,8]
    l1 = create_linked_list([2, 4, 3])
    l2 = create_linked_list([5, 6, 4])
    result = solution.addTwoNumbers(l1, l2)
    print(f"测试1: {print_linked_list(result)}")  # 应该输出 [7, 0, 8]
    
    # 测试用例2: [0] + [0] = [0]
    l1 = create_linked_list([0])
    l2 = create_linked_list([0])
    result = solution.addTwoNumbers(l1, l2)
    print(f"测试2: {print_linked_list(result)}")  # 应该输出 [0]
    
    # 测试用例3: [9,9,9,9,9,9,9] + [9,9,9,9] = [8,9,9,9,0,0,0,1]
    l1 = create_linked_list([9, 9, 9, 9, 9, 9, 9])
    l2 = create_linked_list([9, 9, 9, 9])
    result = solution.addTwoNumbers(l1, l2)
    print(f"测试3: {print_linked_list(result)}")  # 应该输出 [8, 9, 9, 9, 0, 0, 0, 1]
    
    # 测试用例4: 不同长度 [9,9] + [1] = [0,0,1]
    l1 = create_linked_list([9, 9])
    l2 = create_linked_list([1])
    result = solution.addTwoNumbers(l1, l2)
    print(f"测试4: {print_linked_list(result)}")  # 应该输出 [0, 0, 1]