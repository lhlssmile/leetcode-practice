#include <iostream>
#include <string>
struct ListNode{
    int val;
    ListNode *next;
    ListNode():val(0),next(nullptr){}
    ListNode(int val):val(val),next(nullptr){}
    ListNode(int val,struct ListNode* next):val(val),next(next) {}
};
class mergeTwoLinklistSolution{
public:
    ListNode* mergeTwoLists(ListNode* list1,ListNode* list2){
        if(list1 == nullptr && list2 == nullptr) return nullptr;
        auto * dummy = new ListNode(0); // 创建虚拟头节点
        ListNode* tail = dummy; // tail 用来跟踪合并链表的末尾

        while (list1 && list2) {
            if (list1->val < list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // 如果还有剩余节点，直接接上
        if (list1) tail->next = list1;
        if (list2) tail->next = list2;

        return dummy->next; // 返回合并后的链表
    }
    ListNode* mergeTwoList(ListNode* l1,ListNode* l2){
        ListNode head(-1),*dummy = &head;
        ListNode *p1 = l1,*p2 = l2;
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->val < p2->val){
                dummy->next = p1;
                std::cout << p1 << std::endl;
                p1 = p1->next;
            }else{
                dummy->next = p2;
                std::cout << p2 << std::endl;
                p2 = p2->next;
            }
            dummy = dummy->next;
        }
        if(p1) dummy->next = p1;
        if(p2) dummy->next = p2;
        return head.next;
    }
};
int main() {
    // 先创建头节点 0
    auto createList = [](const std::initializer_list<int> &values)->ListNode* {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        for (int val : values) {
            auto * newNode = new ListNode(val);
            if (!head) {
                head = tail = newNode; // 如果链表为空，头尾指针都指向新节点
            } else {
                tail->next = newNode;  // 否则，尾指针指向新节点
                tail = newNode;        // 更新尾指针
            }
        }

        return head;
    };
    // 创建链表1和链表2
    ListNode* list1 = createList({1, 2, 4});
    ListNode* list2 = createList({1, 3, 4});

    // 创建合并对象
    mergeTwoLinklistSolution solution;
    ListNode* mergedHead = solution.mergeTwoList(list1, list2);

    // 打印合并后的链表
    for (auto p = mergedHead; p; p = p->next) {
        std::cout << p->val << (p->next ? "->" : "->NULL\n");
    }

    int num = 22;
    int *ptr = &num;
    int **pptr = &ptr;
    int *aa = *&ptr;
    std::cout << "----------" << std::endl;
    std::cout << pptr << aa << std::endl;
    return 0;
}