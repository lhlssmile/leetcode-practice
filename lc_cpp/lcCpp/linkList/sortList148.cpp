#include <iostream>
#include <initializer_list>
using namespace std;
struct ListNode{
    int val;
    ListNode *next;
    ListNode():val(0),next(nullptr) {}
    ListNode(int val):val(val),next(nullptr) {}
    ListNode(int val,ListNode *next):val(val),next(next) {}
};
class sort_list148 {
public:
    /**
     * use merge sort time complexity can reach O(n logn) space complexity can reach O(1)
     * merge sort's essential thoughts:
     *      1.divide: split linklist to double,till subLinklist only has one node
     *      2.conquer: merge two sorted linklist to become a new sorted linklist
     * detail:
     *      step1:  use slow,fast pointer to reach mid node in the linklist,then split double
     *      step2:  use recursion to sort
     *      step3:  merge sorted linklist
     * @param head tail insert linklist
     * @return sorted linkedlist
     */
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        auto *slow = head,*fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        auto *mid = slow->next;
        slow->next = nullptr;

        auto *left = sortList(head);
        auto *right = sortList(mid);
        return merge(left,right);
    }
private:
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        // 处理剩余节点
        if (l1 != nullptr) {
            tail->next = l1;
        }
        if (l2 != nullptr) {
            tail->next = l2;
        }

        return dummy.next;
    }
};

int main() {
    auto creatList = [](std::initializer_list<int>& values) -> ListNode* {
        auto* dummy = new ListNode(0);
        auto* tail = dummy;
        for(auto const& val : values) {
            auto* p = new ListNode(val,nullptr);
            tail->next = p;
            tail = p;
        }
        return dummy->next;
    };
    std::initializer_list<int> values = {4,2,1,3};
    auto* list = creatList(values);
    sort_list148 solution;
    auto* res = solution.sortList(list);
    auto* p = res;
    while (p) {
        cout << p->val << " ";
        p = p->next;
    }
    return 0;
}
