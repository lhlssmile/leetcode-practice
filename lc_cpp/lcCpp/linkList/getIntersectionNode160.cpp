#include <initializer_list>
#include <iostream>
#include <unordered_set>
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x):val(x),next(nullptr){}
};
class get_intersection_node160 {
public:
    ListNode* getIntersectionNode(ListNode* headA,ListNode* headB) {
        // 用 unordered_set 存储 headA 的节点指针
        std::unordered_set<ListNode*> nodeSet;

        // 遍历 headA，将所有节点加入 set
        ListNode* currA = headA;
        while (currA != nullptr) {
            nodeSet.insert(currA);
            currA = currA->next;
        }

        // 遍历 headB，检查是否有节点在 set 中
        ListNode* currB = headB;
        while (currB != nullptr) {
            if (nodeSet.count(currB) > 0) {
                return currB; // 找到相交节点
            }
            currB = currB->next;
        }

        return nullptr; // 没有相交节点
    }
};

int main() {
    auto createList = [](std::initializer_list<int>& values)->ListNode* {
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        for(auto const& val : values) {
            tail->next = new ListNode(val);
            tail = tail->next;
        }
        ListNode* head = dummy->next;
        delete dummy; // 释放 dummy 节点
        return head;
    };
    std::initializer_list<int> headANodes = {4,1,8,4,5};
    std::initializer_list<int> headBNodes = {5,6,1,8,4,5};
    auto* headA = createList(headANodes);
    auto* headB = createList(headBNodes);
    get_intersection_node160 ps;
    auto* res = ps.getIntersectionNode(headA,headB);
    if(res) {
        std::cout << res->val << std::endl;
    }else {
        std::cout << "no intersection" << std::endl;
    }
    return 0;
}
