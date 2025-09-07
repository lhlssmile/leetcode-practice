// LeetCode 146: LRU缓存
// 设计一个数据结构，支持 get 和 put 操作，并且在容量满时淘汰最近最少使用的元素

#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    int key, val;
    Node* prev;
    Node* next;
    Node() : key(0), val(0), prev(nullptr), next(nullptr) {}
    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int cap;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;
    
    void addToHead(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }
    
    Node* removeTail() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }
    
public:
    LRUCache(int capacity) {
        cap = capacity;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            moveToHead(node);
            return node->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->val = value;
            moveToHead(node);
        } else {
            Node* node = new Node(key, value);
            cache[key] = node;
            addToHead(node);
            if (cache.size() > cap) {
                Node* removed = removeTail();
                cache.erase(removed->key);
                delete removed;
            }
        }
    }
    
    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

void testLRUCache() {
    cout << "=== LRU缓存测试 ===" << endl;
    
    LRUCache lru(2);
    
    lru.put(1, 1);
    lru.put(2, 2);
    cout << "get(1): " << lru.get(1) << endl; // 返回 1
    lru.put(3, 3); // 该操作会使得关键字 2 作废
    cout << "get(2): " << lru.get(2) << endl; // 返回 -1 (未找到)
    lru.put(4, 4); // 该操作会使得关键字 1 作废
    cout << "get(1): " << lru.get(1) << endl; // 返回 -1 (未找到)
    cout << "get(3): " << lru.get(3) << endl; // 返回 3
    cout << "get(4): " << lru.get(4) << endl; // 返回 4
    
    cout << "\n=== C++特性说明 ===" << endl;
    cout << "1. 双向链表: 高效的插入和删除操作" << endl;
    cout << "2. unordered_map: O(1)平均时间复杂度的哈希表" << endl;
    cout << "3. 指针操作: 直接内存管理" << endl;
    cout << "4. 析构函数: 自动资源清理" << endl;
    cout << "5. 面向对象: 封装和数据隐藏" << endl;
}

int main() {
    testLRUCache();
    return 0;
}

/*
C++实现特点:

1. **内存管理**:
   - 手动内存分配和释放
   - 析构函数确保资源清理
   - 指针操作提供高效访问

2. **数据结构**:
   - 双向链表维护访问顺序
   - 哈希表提供O(1)查找
   - 虚拟头尾节点简化边界处理

3. **面向对象**:
   - 类封装实现细节
   - 私有方法隐藏内部操作
   - 构造和析构函数管理生命周期

4. **性能优化**:
   - 内联函数减少调用开销
   - 引用传递避免拷贝
   - 编译时优化

算法复杂度:
- get操作: O(1)
- put操作: O(1)
- 空间复杂度: O(capacity)
*/