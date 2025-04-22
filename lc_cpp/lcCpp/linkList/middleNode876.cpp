struct ListNode {
    int val;
    struct ListNode* next;
    ListNode():val(0),next(nullptr){}
    ListNode(int val):val(val),next(nullptr){}
    ListNode(int val,ListNode* next):val(val),next(next){}
};
#include <vector>
#include <iostream>
using namespace std;
class middle_node876{
public:
    int getListLength(ListNode* head) {
        int n = 0;
        auto* curr = head;
        while (curr) {
            ++n;
            curr = curr->next;
        }
        return n;
    }
    ListNode* middleNode(ListNode* head) {
        int n = this->getListLength(head);
        auto* p = head;
        for(int i = 0;i < n / 2;++i) {
            p = p->next;
        }
        return p;
    }
    ListNode* middleNodeSlowFastPtr(ListNode* head) {
        //长度为奇数时 慢指针在中间 快指针一定指向最后一个node 偶数时候 快指针指向空 慢指针一定在中间。
        auto* fast = head;auto* slow = head;
        while(fast && fast->next ) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    bool hasCycle(ListNode* head) {
        //快指针走两步 慢指针走一步 若有环 一定会相遇
            auto* slow = head;auto* fast = head;
            while(fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;
                if(slow == fast) return true;
            }
            return false;
    }
    ListNode* detectCycle(ListNode* head) {
        auto* slow = head;auto* fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) {
                while (slow != head) {
                    slow = slow->next;
                    head = head->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};
int main() {
    auto* head = new ListNode(0);
    auto* tail = head;
    auto createList = [&head,&tail](std::initializer_list<int> values) -> ListNode* {
        for(auto const& val : values) {
            auto** pp = head ? &tail->next : &head ;
            *pp = new ListNode(val,nullptr);
            tail->next = *pp;
            tail = *pp;
        }
        return head->next;
    };
    auto* list = createList(std::initializer_list<int>{1,2,3,4,5,6});
    middle_node876 ps;
    list = ps.middleNodeSlowFastPtr(list);
    auto* p = list;
    while(p) {
        std::cout << p->val << std::endl;
        p = p->next;
    }
    return 0;
}
