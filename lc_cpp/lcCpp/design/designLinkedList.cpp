// LeetCode 707: 设计链表
// 设计链表的实现。您可以选择使用单链表或双链表。

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// 双向链表节点
struct ListNode {
    int val;
    ListNode* prev;
    ListNode* next;
    
    ListNode(int x = 0) : val(x), prev(nullptr), next(nullptr) {}
};

// 双向链表实现
class MyLinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int size;
    
public:
    MyLinkedList() {
        // 创建哨兵节点
        head = new ListNode();
        tail = new ListNode();
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    
    ~MyLinkedList() {
        // 清理所有节点
        ListNode* current = head;
        while (current) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
    }
    
    int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        
        ListNode* current = head->next;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->val;
    }
    
    void addAtHead(int val) {
        addAtIndex(0, val);
    }
    
    void addAtTail(int val) {
        addAtIndex(size, val);
    }
    
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return;
        }
        
        ListNode* pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred->next;
        }
        
        ListNode* succ = pred->next;
        ListNode* newNode = new ListNode(val);
        
        newNode->prev = pred;
        newNode->next = succ;
        pred->next = newNode;
        succ->prev = newNode;
        
        size++;
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        
        ListNode* pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred->next;
        }
        
        ListNode* toDelete = pred->next;
        ListNode* succ = toDelete->next;
        
        pred->next = succ;
        succ->prev = pred;
        
        delete toDelete;
        size--;
    }
    
    // 辅助函数：打印链表
    void printList() {
        ListNode* current = head->next;
        cout << "[";
        while (current != tail) {
            cout << current->val;
            if (current->next != tail) cout << ", ";
            current = current->next;
        }
        cout << "]" << endl;
    }
    
    int getSize() const {
        return size;
    }
};

// 使用智能指针的现代C++实现
struct SmartNode {
    int val;
    shared_ptr<SmartNode> prev;
    shared_ptr<SmartNode> next;
    
    SmartNode(int x = 0) : val(x) {}
};

class SmartLinkedList {
private:
    shared_ptr<SmartNode> head;
    shared_ptr<SmartNode> tail;
    int size;
    
public:
    SmartLinkedList() {
        head = make_shared<SmartNode>();
        tail = make_shared<SmartNode>();
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    
    int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        
        auto current = head->next;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->val;
    }
    
    void addAtHead(int val) {
        addAtIndex(0, val);
    }
    
    void addAtTail(int val) {
        addAtIndex(size, val);
    }
    
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return;
        }
        
        auto pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred->next;
        }
        
        auto succ = pred->next;
        auto newNode = make_shared<SmartNode>(val);
        
        newNode->prev = pred;
        newNode->next = succ;
        pred->next = newNode;
        succ->prev = newNode;
        
        size++;
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        
        auto pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred->next;
        }
        
        auto toDelete = pred->next;
        auto succ = toDelete->next;
        
        pred->next = succ;
        succ->prev = pred;
        
        size--;
    }
};

// 简化版本：使用vector实现
class VectorLinkedList {
private:
    vector<int> data;
    
public:
    int get(int index) {
        if (index < 0 || index >= data.size()) {
            return -1;
        }
        return data[index];
    }
    
    void addAtHead(int val) {
        data.insert(data.begin(), val);
    }
    
    void addAtTail(int val) {
        data.push_back(val);
    }
    
    void addAtIndex(int index, int val) {
        if (index < 0 || index > data.size()) {
            return;
        }
        data.insert(data.begin() + index, val);
    }
    
    void deleteAtIndex(int index) {
        if (index >= 0 && index < data.size()) {
            data.erase(data.begin() + index);
        }
    }
    
    void printList() {
        cout << "[";
        for (int i = 0; i < data.size(); i++) {
            cout << data[i];
            if (i < data.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

// 模板版本
template<typename T>
class TemplateLinkedList {
private:
    struct Node {
        T val;
        Node* prev;
        Node* next;
        Node(T x = T{}) : val(x), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;
    
public:
    TemplateLinkedList() {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    
    ~TemplateLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    T get(int index) {
        if (index < 0 || index >= size) {
            return T{}; // 返回默认值
        }
        
        Node* current = head->next;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->val;
    }
    
    void addAtIndex(int index, T val) {
        if (index < 0 || index > size) {
            return;
        }
        
        Node* pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred->next;
        }
        
        Node* succ = pred->next;
        Node* newNode = new Node(val);
        
        newNode->prev = pred;
        newNode->next = succ;
        pred->next = newNode;
        succ->prev = newNode;
        
        size++;
    }
};

void testDesignLinkedList() {
    cout << "=== 设计链表测试 ===" << endl;
    
    // 测试标准实现
    cout << "\n--- 标准双向链表实现测试 ---" << endl;
    MyLinkedList list;
    
    list.addAtHead(7);
    list.addAtHead(2);
    list.addAtHead(1);
    cout << "添加头部元素后: ";
    list.printList();
    
    list.addAtIndex(3, 0);
    cout << "在索引3添加0后: ";
    list.printList();
    
    list.deleteAtIndex(2);
    cout << "删除索引2后: ";
    list.printList();
    
    list.addAtHead(6);
    cout << "添加头部6后: ";
    list.printList();
    
    list.addAtTail(4);
    cout << "添加尾部4后: ";
    list.printList();
    
    cout << "获取索引5: " << list.get(5) << endl; // -1
    cout << "获取索引3: " << list.get(3) << endl; // 0
    cout << "获取索引2: " << list.get(2) << endl; // 2
    cout << "获取索引0: " << list.get(0) << endl; // 6
    
    list.deleteAtIndex(0);
    cout << "删除索引0后，获取索引0: " << list.get(0) << endl; // 1
    
    // 测试智能指针版本
    cout << "\n--- 智能指针版本测试 ---" << endl;
    SmartLinkedList smartList;
    smartList.addAtHead(1);
    smartList.addAtTail(3);
    smartList.addAtIndex(1, 2);
    cout << "智能指针版本操作后，获取索引1: " << smartList.get(1) << endl; // 2
    
    // 测试vector版本
    cout << "\n--- Vector版本测试 ---" << endl;
    VectorLinkedList vecList;
    vecList.addAtHead(1);
    vecList.addAtTail(3);
    vecList.addAtIndex(1, 2);
    cout << "Vector版本操作后: ";
    vecList.printList();
    cout << "获取索引1: " << vecList.get(1) << endl; // 2
    
    vecList.deleteAtIndex(1);
    cout << "删除索引1后: ";
    vecList.printList();
    cout << "获取索引1: " << vecList.get(1) << endl; // 3
    
    // 测试模板版本
    cout << "\n--- 模板版本测试 ---" << endl;
    TemplateLinkedList<string> strList;
    strList.addAtIndex(0, "Hello");
    strList.addAtIndex(1, "World");
    cout << "模板版本(string)获取索引0: " << strList.get(0) << endl;
    cout << "模板版本(string)获取索引1: " << strList.get(1) << endl;
    
    cout << "\n=== C++特性说明 ===" << endl;
    cout << "1. 面向对象: 类封装、继承、多态" << endl;
    cout << "2. 手动内存管理: new/delete控制内存" << endl;
    cout << "3. 智能指针: 自动内存管理" << endl;
    cout << "4. 模板编程: 类型安全的泛型" << endl;
    cout << "5. STL容器: vector等高效数据结构" << endl;
}

int main() {
    testDesignLinkedList();
    return 0;
}

/*
C++实现特点:

1. **面向对象编程**:
   - 类封装数据和方法
   - 构造函数和析构函数
   - 访问控制(private/public)

2. **内存管理**:
   - 手动内存管理(new/delete)
   - 智能指针自动管理
   - RAII资源管理

3. **模板编程**:
   - 类型安全的泛型
   - 编译时多态
   - 代码复用

4. **STL容器**:
   - vector动态数组
   - 迭代器访问
   - 算法库支持

5. **现代C++特性**:
   - auto类型推导
   - 智能指针
   - 移动语义

算法复杂度:
- get: O(n)
- addAtHead: O(1)
- addAtTail: O(1)
- addAtIndex: O(n)
- deleteAtIndex: O(n)
- 空间复杂度: O(n)
*/