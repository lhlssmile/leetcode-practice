// LeetCode 146: LRU缓存
// 设计一个数据结构，支持 get 和 put 操作，并且在容量满时淘汰最近最少使用的元素

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10007

typedef struct Node {
    int key;
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    int cap;
    int size;
    Node* head;
    Node* tail;
    Node* hash[HASH_SIZE];
} LRUCache;

Node* createNode(int key, int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->val = val;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

int hash(int key) {
    return (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
}

Node* findInHash(LRUCache* obj, int key) {
    int idx = hash(key);
    Node* curr = obj->hash[idx];
    while (curr) {
        if (curr->key == key) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void addToHash(LRUCache* obj, Node* node) {
    int idx = hash(node->key);
    node->next = obj->hash[idx];
    obj->hash[idx] = node;
}

void removeFromHash(LRUCache* obj, int key) {
    int idx = hash(key);
    Node* curr = obj->hash[idx];
    Node* prev = NULL;
    
    while (curr) {
        if (curr->key == key) {
            if (prev) {
                prev->next = curr->next;
            } else {
                obj->hash[idx] = curr->next;
            }
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

void addToHead(LRUCache* obj, Node* node) {
    node->prev = obj->head;
    node->next = obj->head->next;
    obj->head->next->prev = node;
    obj->head->next = node;
}

void removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void moveToHead(LRUCache* obj, Node* node) {
    removeNode(node);
    addToHead(obj, node);
}

Node* removeTail(LRUCache* obj) {
    Node* node = obj->tail->prev;
    removeNode(node);
    return node;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* obj = (LRUCache*)malloc(sizeof(LRUCache));
    obj->cap = capacity;
    obj->size = 0;
    obj->head = createNode(0, 0);
    obj->tail = createNode(0, 0);
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;
    
    memset(obj->hash, 0, sizeof(obj->hash));
    
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node* node = findInHash(obj, key);
    if (node) {
        moveToHead(obj, node);
        return node->val;
    }
    return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node* node = findInHash(obj, key);
    if (node) {
        node->val = value;
        moveToHead(obj, node);
    } else {
        Node* newNode = createNode(key, value);
        addToHash(obj, newNode);
        addToHead(obj, newNode);
        obj->size++;
        
        if (obj->size > obj->cap) {
            Node* removed = removeTail(obj);
            removeFromHash(obj, removed->key);
            free(removed);
            obj->size--;
        }
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node* curr = obj->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(obj);
}

void testLRUCache() {
    printf("=== LRU缓存测试 ===\n");
    
    LRUCache* lru = lRUCacheCreate(2);
    
    lRUCachePut(lru, 1, 1);
    lRUCachePut(lru, 2, 2);
    printf("get(1): %d\n", lRUCacheGet(lru, 1)); // 返回 1
    lRUCachePut(lru, 3, 3); // 该操作会使得关键字 2 作废
    printf("get(2): %d\n", lRUCacheGet(lru, 2)); // 返回 -1 (未找到)
    lRUCachePut(lru, 4, 4); // 该操作会使得关键字 1 作废
    printf("get(1): %d\n", lRUCacheGet(lru, 1)); // 返回 -1 (未找到)
    printf("get(3): %d\n", lRUCacheGet(lru, 3)); // 返回 3
    printf("get(4): %d\n", lRUCacheGet(lru, 4)); // 返回 4
    
    lRUCacheFree(lru);
    
    printf("\n=== C语言特性说明 ===\n");
    printf("1. 手动内存管理: malloc/free\n");
    printf("2. 指针操作: 直接内存访问\n");
    printf("3. 结构体: 数据封装\n");
    printf("4. 哈希表: 自实现的链式哈希\n");
    printf("5. 函数指针: 可扩展设计\n");
}

int main() {
    testLRUCache();
    return 0;
}

/*
C语言实现特点:

1. **内存管理**:
   - 手动malloc/free管理内存
   - 指针操作提供直接内存访问
   - 需要careful处理内存泄漏

2. **数据结构**:
   - 结构体封装数据
   - 双向链表维护顺序
   - 自实现哈希表

3. **性能特点**:
   - 接近硬件的性能
   - 无垃圾回收开销
   - 编译器优化友好

4. **编程特点**:
   - 过程式编程
   - 显式资源管理
   - 类型安全需要程序员保证

算法复杂度:
- get操作: O(1)平均，O(n)最坏
- put操作: O(1)平均，O(n)最坏
- 空间复杂度: O(capacity)
*/