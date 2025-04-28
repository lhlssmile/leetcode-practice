package LinkList;

// Definition for singly-linked list.
class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}

class LinklistTopicsSolution {
    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        
        while (list1 != null && list2 != null) {
            if (list1.val <= list2.val) {
                current.next = list1;
                list1 = list1.next;
            } else {
                current.next = list2;
                list2 = list2.next;
            }
            current = current.next;
        }
        
        current.next = (list1 != null) ? list1 : list2;
        
        return dummy.next;
    }
    
    // Function to create a linked list using tail insertion
    public ListNode createLinkedList(int[] values) {
        if (values.length == 0) return null;
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;
        for (int val : values) {
            tail.next = new ListNode(val);
            tail = tail.next;
        }
        return dummy.next;
    }
    public static void main(String[] args){
        LinklistTopicsSolution sol = new LinklistTopicsSolution();
        int[] l1 = {1,2,4};
        int[] l2 = {1,3,4};
        ListNode  l1 = sol.createLinkedList();
        ListNode l2 = sol.createLinkedList();
        sol.mergeTwoLists(l1,l2);
    }
}