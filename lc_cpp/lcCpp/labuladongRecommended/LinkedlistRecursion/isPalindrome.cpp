#include <iostream>
struct ListNode{
    int val;
    struct ListNode* next;
    ListNode():val(0),next(nullptr) {}
    ListNode(int val):val(val),next(nullptr){}
    ListNode(int val,ListNode* next):val(val),next(next) {}
};
class isPalindromeSolution{
public:
    int getListLength(ListNode* head){
        int length = 0;
        while(head){
            head = head->next;
            ++length;
        }
        return length;
    }
    bool isPalindrome(ListNode *head){
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        if(fast != nullptr){
            slow = slow->next;
        }
        ListNode* left = head;
        ListNode* right = reverse(slow);
        while(right != nullptr){
            if(left->val != right->val) return false;
            left = left->next;
            right = right->next;
        }
        return true;
    }
    ListNode* reverse(ListNode* head){
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(cur != nullptr){
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur,cur = next;
        }
        return pre;
    }
};
int main() {
    isPalindromeSolution ps;
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
    std::initializer_list<int> values = {3,7,13,22,34,89,34,22,7,3};
    auto* list  = createList(values);
    std::cout << ps.getListLength(list->next) << std::endl;
    std::cout << ps.isPalindrome(list->next) << std::endl;
    return 0;
}
