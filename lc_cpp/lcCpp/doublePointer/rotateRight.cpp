#include <iostream>
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int val): val(val), next(nullptr) {}
    ListNode(int val, struct ListNode* next): val(val), next(next) {}
};

class rotateLinklistSolution {
public:
    int getListLength(ListNode* head) {
        int length = 0;
        while (head != nullptr) {
            length++;
            head = head->next;
        }
        return length;
    }

    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) return head;

        int length = getListLength(head);
        k = k % length;  // 处理k大于链表长度的情况
        if (k == 0) return head;

        ListNode* kth_node_before = head;
        ListNode* kth_node_after = head;

        // 移动kth_node_before到倒数第k个节点前
        for (int i = 0; i < length - k - 1; ++i) {
            kth_node_before = kth_node_before->next;
        }

        // kth_node_after 指向倒数第k个节点
        kth_node_after = kth_node_before->next;

        // 断开链表，构成两个部分
        kth_node_before->next = nullptr;

        // 连接后部分到前部分
        ListNode* new_head = kth_node_after;
        ListNode* tail = kth_node_after;

        // 找到新链表的尾节点
        while (tail->next != nullptr) {
            tail = tail->next;
        }

        // 拼接头部
        tail->next = head;

        return new_head;
    }

    void traverseList(ListNode* head) {
        ListNode* current = head;  // 当前节点指针
        while (current != nullptr) {
            // 输出当前节点的值
            std::cout << current->val << " ";
            // 移动到下一个节点
            current = current->next;
        }
        std::cout << std::endl;  // 遍历完毕后换行
    }
};

int main() {
    rotateLinklistSolution ps;
    auto* head = new ListNode(1);  // 头节点不再是0
    auto* r = head;
    for (int i = 2; i < 6; ++i) {  // 创建链表节点 2, 4, 6, 8, 10
        auto* p = new ListNode(i * 2);
        r->next = p;
        r = p;
    }

    std::cout << "Original List:" << std::endl;
    ps.traverseList(head);  // 打印原始链表

    int k = 2;
    std::cout << "---------------" << std::endl;

    // 旋转链表并打印
    auto* new_list = ps.rotateRight(head, k);
    ps.traverseList(new_list);

    // 清理内存
    delete head;
    return 0;
}
