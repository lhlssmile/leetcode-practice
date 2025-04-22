#include <iostream>
#include <vector>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode():val(0),next(nullptr) {}
    ListNode(int val):val(val),next(nullptr) {}
    ListNode(int val,ListNode* next) :val(val),next(next) {}
};
class merge_k_lists23 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty())   return {};
        return mergeK(lists,0,lists.size() - 1);
    }
private:
    ListNode* mergeK(vector<ListNode*>& lists,int left,int right) {
        if(left == right)   return lists[left];
        int mid = left + (right - left ) / 2;
        auto* l1 = mergeK(lists,left,mid);
        auto* l2 = mergeK(lists,mid + 1,right);
        return merge(l1,l2);
    }
    ListNode* merge(ListNode* l1,ListNode* l2) {
        if(!l1) return l2;
        if(!l2) return l1;
        auto* dummy = new ListNode(0);
        auto* tail = dummy;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            }else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if (l1 != nullptr) {
            tail->next = l1;
        }
        if(l2 != nullptr) {
            tail->next = l2;
        }
        return dummy->next;
    }
};

int main() {
    merge_k_lists23 solution;
    auto createList = [](std::initializer_list<int>& values) -> ListNode* {
        auto* dummy = new ListNode(0);
        auto* tail = dummy;
        for(auto const& val : values) {
            auto* p = new ListNode(val,nullptr);
            tail->next = p;
            tail = p;
      }
        return dummy->next;
    };
    std::initializer_list<int> list1_values = {1,4,5};
    std::initializer_list<int> list2_values = {1,3,4};
    std::initializer_list<int> list3_values = {2,6};
    auto* list1 = createList(list1_values);
    auto* list2 = createList(list2_values);
    auto* list3 = createList(list3_values);
    vector<ListNode*> lists = {list1,list2,list3};
    auto* res = solution.mergeKLists(lists);
    auto* p = res;
    while (p) {
        cout << p->val << " ";
        p = p->next;
    }
    return 0;
}
