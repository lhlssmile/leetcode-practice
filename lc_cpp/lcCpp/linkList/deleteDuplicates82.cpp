    #include <iostream>
    using namespace std;
    struct ListNode {
        int val;
        struct ListNode* next;
        ListNode():val(0),next(nullptr){}
        ListNode(int val):val(val),next(nullptr){}
        ListNode(int val,ListNode* next):val(val),next(next){}
    };
    class delete_duplicates82 {
    public:
        ListNode* deleteDuplicates(ListNode* head) {
            auto* dummy = new ListNode(0,head);
            auto* curr = dummy;
            while(curr->next && curr->next->next) {
                int val = curr->next->val;
                if(val == curr->next->next->val) {
                    while(curr->next->val == val && curr->next) {
                        curr->next = curr->next->next;
                    }
                }else {
                    curr = curr->next;
                }
            }
            return dummy->next;
        }
    };

    int main() {
        auto* head = new ListNode(0);
        auto* tail = head;
        auto createList = [&head,&tail](std::initializer_list<int> values) -> ListNode* {
            for(auto const& val : values) {
                auto** pp = head ? &tail->next : &head;
                *pp = new ListNode(val,nullptr);
                tail->next = *pp;
                tail = *pp;
            }
            return head->next;
        };
        auto* list = createList(std::initializer_list<int>{1,2,3,3,4,4,5});
        delete_duplicates82 ps;
        list = ps.deleteDuplicates(list);
        auto* p = list;
        while(p) {
            std::cout << p->val << " ";
            p = p->next;
        }
        return 0;
    }
