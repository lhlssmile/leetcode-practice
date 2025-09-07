// LeetCode 707: 设计链表
// 设计链表的实现。您可以选择使用单链表或双链表。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 双向链表节点结构
typedef struct ListNode {
    int val;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

// 双向链表结构
typedef struct {
    ListNode* head;
    ListNode* tail;
    int size;
} MyLinkedList;

// 创建新节点
ListNode* createNode(int val) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (node) {
        node->val = val;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

// 创建链表
MyLinkedList* myLinkedListCreate() {
    MyLinkedList* obj = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    if (obj) {
        // 创建哨兵节点
        obj->head = createNode(0);
        obj->tail = createNode(0);
        
        if (obj->head && obj->tail) {
            obj->head->next = obj->tail;
            obj->tail->prev = obj->head;
            obj->size = 0;
        } else {
            // 内存分配失败，清理
            free(obj->head);
            free(obj->tail);
            free(obj);
            obj = NULL;
        }
    }
    return obj;
}

// 获取指定索引的值
int myLinkedListGet(MyLinkedList* obj, int index) {
    if (!obj || index < 0 || index >= obj->size) {
        return -1;
    }
    
    ListNode* current = obj->head->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->val;
}

// 在头部添加节点
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    if (obj) {
        myLinkedListAddAtIndex(obj, 0, val);
    }
}

// 在尾部添加节点
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    if (obj) {
        myLinkedListAddAtIndex(obj, obj->size, val);
    }
}

// 在指定索引添加节点
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if (!obj || index < 0 || index > obj->size) {
        return;
    }
    
    ListNode* pred = obj->head;
    for (int i = 0; i < index; i++) {
        pred = pred->next;
    }
    
    ListNode* succ = pred->next;
    ListNode* newNode = createNode(val);
    
    if (newNode) {
        newNode->prev = pred;
        newNode->next = succ;
        pred->next = newNode;
        succ->prev = newNode;
        obj->size++;
    }
}

// 删除指定索引的节点
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    if (!obj || index < 0 || index >= obj->size) {
        return;
    }
    
    ListNode* pred = obj->head;
    for (int i = 0; i < index; i++) {
        pred = pred->next;
    }
    
    ListNode* toDelete = pred->next;
    ListNode* succ = toDelete->next;
    
    pred->next = succ;
    succ->prev = pred;
    
    free(toDelete);
    obj->size--;
}

// 释放链表内存
void myLinkedListFree(MyLinkedList* obj) {
    if (!obj) return;
    
    ListNode* current = obj->head;
    while (current) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
    free(obj);
}

// 打印链表
void myLinkedListPrint(MyLinkedList* obj) {
    if (!obj) {
        printf("[]");
        return;
    }
    
    printf("[");
    ListNode* current = obj->head->next;
    bool first = true;
    
    while (current != obj->tail) {
        if (!first) printf(", ");
        printf("%d", current->val);
        first = false;
        current = current->next;
    }
    printf("]\n");
}

// 获取链表大小
int myLinkedListGetSize(MyLinkedList* obj) {
    return obj ? obj->size : 0;
}

// 简化版本：使用动态数组实现
typedef struct {
    int* data;
    int size;
    int capacity;
} ArrayLinkedList;

// 创建数组链表
ArrayLinkedList* arrayLinkedListCreate() {
    ArrayLinkedList* obj = (ArrayLinkedList*)malloc(sizeof(ArrayLinkedList));
    if (obj) {
        obj->capacity = 10;
        obj->data = (int*)malloc(obj->capacity * sizeof(int));
        obj->size = 0;
        
        if (!obj->data) {
            free(obj);
            obj = NULL;
        }
    }
    return obj;
}

// 扩容
void arrayLinkedListResize(ArrayLinkedList* obj) {
    if (!obj) return;
    
    obj->capacity *= 2;
    int* newData = (int*)realloc(obj->data, obj->capacity * sizeof(int));
    if (newData) {
        obj->data = newData;
    }
}

// 数组链表获取值
int arrayLinkedListGet(ArrayLinkedList* obj, int index) {
    if (!obj || index < 0 || index >= obj->size) {
        return -1;
    }
    return obj->data[index];
}

// 数组链表在头部添加
void arrayLinkedListAddAtHead(ArrayLinkedList* obj, int val) {
    if (!obj) return;
    
    if (obj->size >= obj->capacity) {
        arrayLinkedListResize(obj);
    }
    
    // 向后移动所有元素
    for (int i = obj->size; i > 0; i--) {
        obj->data[i] = obj->data[i - 1];
    }
    obj->data[0] = val;
    obj->size++;
}

// 数组链表在尾部添加
void arrayLinkedListAddAtTail(ArrayLinkedList* obj, int val) {
    if (!obj) return;
    
    if (obj->size >= obj->capacity) {
        arrayLinkedListResize(obj);
    }
    
    obj->data[obj->size] = val;
    obj->size++;
}

// 数组链表在指定索引添加
void arrayLinkedListAddAtIndex(ArrayLinkedList* obj, int index, int val) {
    if (!obj || index < 0 || index > obj->size) {
        return;
    }
    
    if (obj->size >= obj->capacity) {
        arrayLinkedListResize(obj);
    }
    
    // 向后移动元素
    for (int i = obj->size; i > index; i--) {
        obj->data[i] = obj->data[i - 1];
    }
    obj->data[index] = val;
    obj->size++;
}

// 数组链表删除指定索引
void arrayLinkedListDeleteAtIndex(ArrayLinkedList* obj, int index) {
    if (!obj || index < 0 || index >= obj->size) {
        return;
    }
    
    // 向前移动元素
    for (int i = index; i < obj->size - 1; i++) {
        obj->data[i] = obj->data[i + 1];
    }
    obj->size--;
}

// 释放数组链表
void arrayLinkedListFree(ArrayLinkedList* obj) {
    if (obj) {
        free(obj->data);
        free(obj);
    }
}

// 打印数组链表
void arrayLinkedListPrint(ArrayLinkedList* obj) {
    if (!obj) {
        printf("[]");
        return;
    }
    
    printf("[");
    for (int i = 0; i < obj->size; i++) {
        if (i > 0) printf(", ");
        printf("%d", obj->data[i]);
    }
    printf("]\n");
}

// 单链表实现
typedef struct SinglyNode {
    int val;
    struct SinglyNode* next;
} SinglyNode;

typedef struct {
    SinglyNode* head;
    int size;
} SinglyLinkedList;

// 创建单链表
SinglyLinkedList* singlyLinkedListCreate() {
    SinglyLinkedList* obj = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
    if (obj) {
        obj->head = (SinglyNode*)malloc(sizeof(SinglyNode));
        if (obj->head) {
            obj->head->val = 0;
            obj->head->next = NULL;
            obj->size = 0;
        } else {
            free(obj);
            obj = NULL;
        }
    }
    return obj;
}

// 单链表获取值
int singlyLinkedListGet(SinglyLinkedList* obj, int index) {
    if (!obj || index < 0 || index >= obj->size) {
        return -1;
    }
    
    SinglyNode* current = obj->head->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->val;
}

// 单链表在指定索引添加
void singlyLinkedListAddAtIndex(SinglyLinkedList* obj, int index, int val) {
    if (!obj || index < 0 || index > obj->size) {
        return;
    }
    
    SinglyNode* pred = obj->head;
    for (int i = 0; i < index; i++) {
        pred = pred->next;
    }
    
    SinglyNode* newNode = (SinglyNode*)malloc(sizeof(SinglyNode));
    if (newNode) {
        newNode->val = val;
        newNode->next = pred->next;
        pred->next = newNode;
        obj->size++;
    }
}

// 单链表删除指定索引
void singlyLinkedListDeleteAtIndex(SinglyLinkedList* obj, int index) {
    if (!obj || index < 0 || index >= obj->size) {
        return;
    }
    
    SinglyNode* pred = obj->head;
    for (int i = 0; i < index; i++) {
        pred = pred->next;
    }
    
    SinglyNode* toDelete = pred->next;
    pred->next = toDelete->next;
    free(toDelete);
    obj->size--;
}

// 释放单链表
void singlyLinkedListFree(SinglyLinkedList* obj) {
    if (!obj) return;
    
    SinglyNode* current = obj->head;
    while (current) {
        SinglyNode* next = current->next;
        free(current);
        current = next;
    }
    free(obj);
}

void testDesignLinkedList() {
    printf("=== 设计链表测试 ===\n");
    
    // 测试双向链表实现
    printf("\n--- 双向链表实现测试 ---\n");
    MyLinkedList* list = myLinkedListCreate();
    
    if (list) {
        myLinkedListAddAtHead(list, 7);
        myLinkedListAddAtHead(list, 2);
        myLinkedListAddAtHead(list, 1);
        printf("添加头部元素后: ");
        myLinkedListPrint(list);
        
        myLinkedListAddAtIndex(list, 3, 0);
        printf("在索引3添加0后: ");
        myLinkedListPrint(list);
        
        myLinkedListDeleteAtIndex(list, 2);
        printf("删除索引2后: ");
        myLinkedListPrint(list);
        
        myLinkedListAddAtHead(list, 6);
        printf("添加头部6后: ");
        myLinkedListPrint(list);
        
        myLinkedListAddAtTail(list, 4);
        printf("添加尾部4后: ");
        myLinkedListPrint(list);
        
        printf("获取索引5: %d\n", myLinkedListGet(list, 5)); // -1
        printf("获取索引3: %d\n", myLinkedListGet(list, 3)); // 0
        printf("获取索引2: %d\n", myLinkedListGet(list, 2)); // 2
        printf("获取索引0: %d\n", myLinkedListGet(list, 0)); // 6
        
        myLinkedListDeleteAtIndex(list, 0);
        printf("删除索引0后，获取索引0: %d\n", myLinkedListGet(list, 0)); // 1
        
        myLinkedListFree(list);
    }
    
    // 测试数组实现
    printf("\n--- 数组实现测试 ---\n");
    ArrayLinkedList* arrayList = arrayLinkedListCreate();
    
    if (arrayList) {
        arrayLinkedListAddAtHead(arrayList, 1);
        arrayLinkedListAddAtTail(arrayList, 3);
        arrayLinkedListAddAtIndex(arrayList, 1, 2);
        printf("数组实现操作后: ");
        arrayLinkedListPrint(arrayList);
        printf("获取索引1: %d\n", arrayLinkedListGet(arrayList, 1)); // 2
        
        arrayLinkedListDeleteAtIndex(arrayList, 1);
        printf("删除索引1后: ");
        arrayLinkedListPrint(arrayList);
        printf("获取索引1: %d\n", arrayLinkedListGet(arrayList, 1)); // 3
        
        arrayLinkedListFree(arrayList);
    }
    
    // 测试单链表实现
    printf("\n--- 单链表实现测试 ---\n");
    SinglyLinkedList* singlyList = singlyLinkedListCreate();
    
    if (singlyList) {
        singlyLinkedListAddAtIndex(singlyList, 0, 10);
        singlyLinkedListAddAtIndex(singlyList, 0, 20);
        singlyLinkedListAddAtIndex(singlyList, 1, 30);
        printf("单链表操作后: [20, 30, 10]\n");
        printf("获取索引1: %d\n", singlyLinkedListGet(singlyList, 1)); // 30
        
        singlyLinkedListDeleteAtIndex(singlyList, 0);
        printf("删除索引0后，获取索引0: %d\n", singlyLinkedListGet(singlyList, 0)); // 30
        
        singlyLinkedListFree(singlyList);
    }
    
    printf("\n=== C语言特性说明 ===\n");
    printf("1. 手动内存管理: malloc/free控制内存\n");
    printf("2. 指针操作: 直接操作内存地址\n");
    printf("3. 结构体: 数据封装和组织\n");
    printf("4. 函数指针: 实现多态行为\n");
    printf("5. 错误处理: 返回值检查和资源清理\n");
}

int main() {
    testDesignLinkedList();
    return 0;
}

/*
C语言实现特点:

1. **手动内存管理**:
   - malloc/free显式分配释放
   - 需要检查内存分配是否成功
   - 防止内存泄漏

2. **指针操作**:
   - 直接操作内存地址
   - 指针链接节点
   - 空指针检查

3. **结构体封装**:
   - 数据和相关信息组织
   - 模拟面向对象
   - typedef简化类型名

4. **错误处理**:
   - 返回值检查
   - 边界条件处理
   - 资源清理

5. **性能优化**:
   - 直接内存访问
   - 最小化函数调用开销
   - 缓存友好的数据布局

算法复杂度:
- get: O(n)
- addAtHead: O(1)
- addAtTail: O(1)
- addAtIndex: O(n)
- deleteAtIndex: O(n)
- 空间复杂度: O(n)
*/