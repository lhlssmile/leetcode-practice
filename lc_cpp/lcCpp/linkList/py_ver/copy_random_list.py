#copy random list

class Node:
	def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
		self.val = int(x)
		self.next = next
		self.random = random
class Solution:

	def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
		# copy node insert after ori list
		if not head:
			return None		
		curr = head
		
		while curr:
			new_node = Node(curr.val,curr.next)
			curr.next = new_node
			curr = new_node.next

		curr = head
		
		while curr:
			if curr.random:
				curr.next.random = curr.random.next
			curr = curr.next.next
		dummy = Node(0)
		
		curr_new = dummy
		curr = head
		

		while curr:
			curr_new.next = curr.next
			curr.next = curr.next.next
			curr = curr.next
			curr_new = curr_new.next
		return dummy.next
