#include <initializer_list>
#include <iostream>
#include <vector>
struct ListNode {
    int val;
    struct ListNode* next;
    ListNode():val(0),next(nullptr){}
    ListNode(int val):val(val),next(nullptr){}
    ListNode(int val,ListNode* next):val(val),next(next){}
};
class reverse_list_206 {
public:
    ListNode* reverseList(ListNode* head) {
        if(head->next == nullptr) return nullptr;
        if(head->next->next == nullptr) return head->next;
        ListNode* pre = nullptr;ListNode* curr = head->next;

        while (curr != nullptr) {
            ListNode* nxt = curr->next;
            curr->next = pre;
            pre = curr;
            curr = nxt;
        }
        return pre;
    }
};

int main() {
    auto* head = new ListNode(0);
    auto* tail = head;
    auto createList = [&head,&tail](std::initializer_list<int>& values) ->ListNode* {
        for(const auto& val : values){
            ListNode** pp = head ? &tail->next : &head;
            *pp = new ListNode(val, nullptr);
            tail->next = *pp;
            tail = *pp;
        }
        return head;
    };
    std::initializer_list<int> values = {1,2,3,4,5};
    auto list = createList(values);
    reverse_list_206 ps;
    list = ps.reverseList(list);
    auto* p = list;
    while(p) {
        std::cout << p->val << " ";
        p = p->next;
    }
    return 0;
}
