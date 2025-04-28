#include <initializer_list>
#include <iostream>

struct ListNode {
    int val;
    struct ListNode* next;
    ListNode():val(0),next(nullptr){}
    ListNode(int val):val(val),next(nullptr){}
    ListNode(int val,ListNode* next):val(val),next(next){}
};
class reverse_k_group25 {
public:
    int getListLength(ListNode* head) {
        auto* curr = head;
        int n = 0;
        while (curr) {
            curr = curr->next;
            ++n;
        }
        return n;
    }
    ListNode* reverseKGroup(ListNode* head,int k) {
        auto* dummy = new ListNode(0,head);
        int n = this->getListLength(head);
        ListNode* pre = nullptr;auto* p0 = dummy;
        while(n >= k) {
            n -= k;
            auto* curr = p0->next;
            for(int i = 0;i < k;++i) {
                auto* nxt = curr->next;
                curr->next = pre;
                pre = curr;
                curr = nxt;
            }
            auto* nxt = p0->next;
            p0->next->next = curr;
            p0->next = pre;
            p0 = nxt;
        }
        return dummy->next;
    }
};

int main() {
    auto* head = new ListNode(0);
    auto* tail = head;
    auto createList = [&head,&tail](std::initializer_list<int> values) -> ListNode* {
        for(auto const& val : values) {
            auto** pp = head ? & tail->next : &head;
            *pp = new ListNode(val,nullptr);
            tail->next = *pp;
            tail = *pp;
        }
        return head->next;
    };
    auto* list = createList(std::initializer_list<int>{1,2,3,4,5});
    //两个两个改
    reverse_k_group25 ps;
    list = ps.reverseKGroup(list,2);
    auto*p = list;
    while(p) {
        std::cout << p->val << std::endl;
        p = p->next;
    }
    return 0;
}
