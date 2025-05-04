from typing import Optional


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

        current.next = list1 if list1 else list2
        return dummy.next

    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        dummy.next = head
        p0 = dummy

        while p0.next and p0.next.next:
            a = p0.next
            b = a.next

            # swap
            a.next = b.next
            b.next = a
            p0.next = b

            # move p0 forward
            p0 = a

        return dummy.next

    # Create linked list from list[int]
    def createLinkedList(self, values: list[int]) -> Optional[ListNode]:
        if not values:
            return None
        dummy = ListNode(0)
        tail = dummy
        for val in values:
            tail.next = ListNode(val)
            tail = tail.next
        return dummy.next

    # Print linked list for debugging
    def printList(self, head: Optional[ListNode]) -> None:
        while head:
            print(head.val, end=" -> ")
            head = head.next
        print("None")


if __name__ == "__main__":
    sol = Solution()

    # 测试 mergeTwoLists
    l1 = [1, 2, 4]
    l2 = [1, 3, 4]
    node1 = sol.createLinkedList(l1)
    node2 = sol.createLinkedList(l2)
    merged = sol.mergeTwoLists(node1, node2)
    print("Merged List:")
    sol.printList(merged)

    # 测试 swapPairs
    vals = [1, 2, 3, 4]
    linked = sol.createLinkedList(vals)
    swapped = sol.swapPairs(linked)
    print("Swapped Pairs List:")
    sol.printList(swapped)
