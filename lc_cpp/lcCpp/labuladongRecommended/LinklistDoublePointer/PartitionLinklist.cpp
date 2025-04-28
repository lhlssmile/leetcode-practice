#include <iostream>
struct ListNode{
    int val;
    struct ListNode* next;
    ListNode():val(0),next(nullptr){}
    ListNode(int val):val(val),next(nullptr){}
    ListNode(int val,struct ListNode* next):val(val),next(next){}
};
class PartitionLinklistSolution{
public:
    ListNode* partition(ListNode* head,int x){
        ListNode small_dummy(0); // 小鱼虚拟头
        ListNode large_dummy(0); // 大鱼虚拟头
        ListNode* small = &small_dummy;
        ListNode* large = &large_dummy;

        while (head) {
            if (head->val < x) { // 分类小鱼
                small->next = head;
                small = small->next;
            } else {             // 分类大鱼
                large->next = head;
                large = large->next;
            }
            head = head->next;
        }

        // 连接小鱼和大鱼
        small->next = large_dummy.next;
        large->next = nullptr; // 防止循环

        return small_dummy.next;
    }
    ListNode* partitionMine(ListNode* head,int x){
        auto *small = new ListNode(0);
        auto *large = new ListNode(0);
        auto *small_seg = small;
        auto *large_seg = large;
        while(head){
            if(head->val < x){
                small_seg->next = head;
                small_seg = small_seg->next;
            }else{
                large_seg->next = head;
                large_seg = large_seg->next;
            }
            head = head->next;
        }
        small_seg->next = large->next;
        large_seg->next = nullptr;
        return small->next;
    }
};

int main() {
    PartitionLinklistSolution ps;
    auto createList = [](std::initializer_list<int>& values) ->ListNode* {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        for(const auto& val : values){
            auto* newNode = new ListNode(val, nullptr);
            if(!head){
                head = tail = newNode;
            }else{
                tail->next = newNode;
                tail = newNode;
            }
        }
        return head;
    };

    std::initializer_list<int> values = {1,4,3,2,5,2};
    auto *head = createList(values);

    // 正确遍历原链表
    std::cout << "原链表：";
    for(auto p = head; p; p = p->next){
        std::cout << p->val << (p->next ? "->" : "\n");
    }

    auto* list = ps.partitionMine(head, 3);

    // 正确遍历分割后的链表
    std::cout << "分割后：";
    for(auto p = list; p; p = p->next){
        std::cout << p->val << (p->next ? "->" : "\n");
    }

    // 正确释放分割后的链表
    while (list) {
        auto* temp = list;
        list = list->next;
        delete temp;
    }
    return 0;
}
