from typing import List
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        current = dummy
        
        while list1 and list2:
            if list1.val <= list2.val:
                current.next = list1
                list1 = list1.next
            else:
                current.next = list2
                list2 = list2.next
            current = current.next
        
        # Append remaining nodes
        current.next = list1 if list1 else list2
        
        return dummy.next

    # Function to create a linked list using tail insertion
    def createLinkedList(self, values: list[int]) -> Optional[ListNode]:
        if not values:
            return None
        dummy = ListNode(0)
        tail = dummy
        for val in values:
            tail.next = ListNode(val)
            tail = tail.next
        return dummy.next


if __name__ == "__main__":
    sol = Solution()
    l1 = [1,2,4]
    l2 = [1,3,4]
    sol.createLinkedList(l1)
    sol.createLinkedList(l2)

    sol.mergeTwoLists(l1,l2)