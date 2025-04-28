#include <initializer_list>
#include <iostream>

struct ListNode {
    int val;
    struct ListNode* next;
    ListNode():val(0),next(nullptr){}
    ListNode(int val):val(val),next(nullptr){}
    ListNode(int val,ListNode* next):val(val),next(next){}
};

class reverse_between92 {
public:
    ListNode* reverseBetween(ListNode* head,int left,int right) {
        auto* dummy = head;
        auto* reversePre = head;
        for(int i = 0; i < left - 1;++i) {
            reversePre = reversePre->next;
        }
        ListNode* pre = nullptr;
        auto* curr = reversePre->next;
        for(int i = 0;i < right - left + 1;++i) {
            auto* nxt = curr->next;
            curr->next = pre;
            pre = curr;
            curr = nxt;
        }
        reversePre->next->next = curr;
        reversePre->next = pre;
        return dummy->next;
    }
};

int main() {
    auto* head = new ListNode(0);
    auto* tail = head;
    auto createList = [&head,&tail](std::initializer_list<int> values) -> ListNode* {
        for(auto const& val : values) {
            ListNode** pp = head ? &tail->next : &head;
            *pp = new ListNode(val,nullptr);
            tail->next = *pp;
            tail = *pp;
        }
        return head;
    };
    auto list = createList(std::initializer_list<int>{1,2,3,4,5});
    reverse_between92 ps;
    list = ps.reverseBetween(list,2,4);
    auto* p = list;
    while(p) {
        std::cout << p->val << std::endl;
        p = p->next;
    }
    return 0;
}
