// LeetCode 707: 设计链表
// 设计链表的实现。您可以选择使用单链表或双链表。

// 双向链表节点
class ListNode {
    constructor(val = 0) {
        this.val = val;
        this.prev = null;
        this.next = null;
    }
    
    toString() {
        return `ListNode(${this.val})`;
    }
}

// 双向链表实现
class MyLinkedList {
    constructor() {
        // 创建哨兵节点
        this.head = new ListNode();
        this.tail = new ListNode();
        this.head.next = this.tail;
        this.tail.prev = this.head;
        this.size = 0;
    }
    
    /**
     * 获取链表中第 index 个节点的值
     * @param {number} index
     * @return {number}
     */
    get(index) {
        if (index < 0 || index >= this.size) {
            return -1;
        }
        
        let current = this.head.next;
        for (let i = 0; i < index; i++) {
            current = current.next;
        }
        return current.val;
    }
    
    /**
     * 在链表第一个元素之前添加一个值为 val 的节点
     * @param {number} val
     * @return {void}
     */
    addAtHead(val) {
        this.addAtIndex(0, val);
    }
    
    /**
     * 将值为 val 的节点追加到链表的最后一个元素
     * @param {number} val
     * @return {void}
     */
    addAtTail(val) {
        this.addAtIndex(this.size, val);
    }
    
    /**
     * 在链表中的第 index 个节点之前添加值为 val 的节点
     * @param {number} index
     * @param {number} val
     * @return {void}
     */
    addAtIndex(index, val) {
        if (index < 0 || index > this.size) {
            return;
        }
        
        let pred = this.head;
        for (let i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        const succ = pred.next;
        const newNode = new ListNode(val);
        
        newNode.prev = pred;
        newNode.next = succ;
        pred.next = newNode;
        succ.prev = newNode;
        
        this.size++;
    }
    
    /**
     * 如果索引 index 有效，则删除链表中的第 index 个节点
     * @param {number} index
     * @return {void}
     */
    deleteAtIndex(index) {
        if (index < 0 || index >= this.size) {
            return;
        }
        
        let pred = this.head;
        for (let i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        const toDelete = pred.next;
        const succ = toDelete.next;
        
        pred.next = succ;
        succ.prev = pred;
        
        this.size--;
    }
    
    /**
     * 获取链表大小
     * @return {number}
     */
    getSize() {
        return this.size;
    }
    
    /**
     * 转换为数组
     * @return {number[]}
     */
    toArray() {
        const result = [];
        let current = this.head.next;
        while (current !== this.tail) {
            result.push(current.val);
            current = current.next;
        }
        return result;
    }
    
    /**
     * 字符串表示
     * @return {string}
     */
    toString() {
        return JSON.stringify(this.toArray());
    }
}

// 使用数组实现的链表
class ArrayLinkedList {
    constructor() {
        this.data = [];
    }
    
    get(index) {
        return (index >= 0 && index < this.data.length) ? this.data[index] : -1;
    }
    
    addAtHead(val) {
        this.data.unshift(val);
    }
    
    addAtTail(val) {
        this.data.push(val);
    }
    
    addAtIndex(index, val) {
        if (index >= 0 && index <= this.data.length) {
            this.data.splice(index, 0, val);
        }
    }
    
    deleteAtIndex(index) {
        if (index >= 0 && index < this.data.length) {
            this.data.splice(index, 1);
        }
    }
    
    toString() {
        return JSON.stringify(this.data);
    }
}

// 单链表节点
class SinglyListNode {
    constructor(val = 0) {
        this.val = val;
        this.next = null;
    }
}

// 单链表实现
class SinglyLinkedList {
    constructor() {
        this.head = new SinglyListNode(); // 哨兵节点
        this.size = 0;
    }
    
    get(index) {
        if (index < 0 || index >= this.size) {
            return -1;
        }
        
        let current = this.head.next;
        for (let i = 0; i < index; i++) {
            current = current.next;
        }
        return current.val;
    }
    
    addAtHead(val) {
        this.addAtIndex(0, val);
    }
    
    addAtTail(val) {
        this.addAtIndex(this.size, val);
    }
    
    addAtIndex(index, val) {
        if (index < 0 || index > this.size) {
            return;
        }
        
        let pred = this.head;
        for (let i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        const newNode = new SinglyListNode(val);
        newNode.next = pred.next;
        pred.next = newNode;
        
        this.size++;
    }
    
    deleteAtIndex(index) {
        if (index < 0 || index >= this.size) {
            return;
        }
        
        let pred = this.head;
        for (let i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        pred.next = pred.next.next;
        this.size--;
    }
}

// 函数式编程风格的链表
class FunctionalLinkedList {
    constructor() {
        this.data = [];
    }
    
    get(index) {
        return this.data.at(index) ?? -1;
    }
    
    addAtHead(val) {
        this.data = [val, ...this.data];
    }
    
    addAtTail(val) {
        this.data = [...this.data, val];
    }
    
    addAtIndex(index, val) {
        if (index >= 0 && index <= this.data.length) {
            this.data = [
                ...this.data.slice(0, index),
                val,
                ...this.data.slice(index)
            ];
        }
    }
    
    deleteAtIndex(index) {
        if (index >= 0 && index < this.data.length) {
            this.data = [
                ...this.data.slice(0, index),
                ...this.data.slice(index + 1)
            ];
        }
    }
    
    toString() {
        return JSON.stringify(this.data);
    }
}

// 使用Map实现的链表（保持插入顺序）
class MapLinkedList {
    constructor() {
        this.data = new Map();
        this.size = 0;
    }
    
    get(index) {
        return this.data.has(index) ? this.data.get(index) : -1;
    }
    
    addAtHead(val) {
        // 所有索引向后移动
        const newData = new Map();
        newData.set(0, val);
        for (const [key, value] of this.data) {
            newData.set(key + 1, value);
        }
        this.data = newData;
        this.size++;
    }
    
    addAtTail(val) {
        this.data.set(this.size, val);
        this.size++;
    }
    
    addAtIndex(index, val) {
        if (index < 0 || index > this.size) {
            return;
        }
        
        const newData = new Map();
        for (let i = 0; i < index; i++) {
            newData.set(i, this.data.get(i));
        }
        newData.set(index, val);
        for (let i = index; i < this.size; i++) {
            newData.set(i + 1, this.data.get(i));
        }
        this.data = newData;
        this.size++;
    }
    
    deleteAtIndex(index) {
        if (index < 0 || index >= this.size) {
            return;
        }
        
        const newData = new Map();
        for (let i = 0; i < index; i++) {
            newData.set(i, this.data.get(i));
        }
        for (let i = index + 1; i < this.size; i++) {
            newData.set(i - 1, this.data.get(i));
        }
        this.data = newData;
        this.size--;
    }
    
    toArray() {
        return Array.from(this.data.values());
    }
    
    toString() {
        return JSON.stringify(this.toArray());
    }
}

// 使用WeakMap的链表（演示WeakMap特性）
class WeakMapLinkedList {
    constructor() {
        this.nodes = new WeakMap();
        this.head = {};
        this.tail = {};
        this.nodes.set(this.head, { next: this.tail, val: null });
        this.nodes.set(this.tail, { prev: this.head, val: null });
        this.size = 0;
    }
    
    get(index) {
        if (index < 0 || index >= this.size) {
            return -1;
        }
        
        let current = this.nodes.get(this.head).next;
        for (let i = 0; i < index; i++) {
            current = this.nodes.get(current).next;
        }
        return this.nodes.get(current).val;
    }
    
    addAtIndex(index, val) {
        if (index < 0 || index > this.size) {
            return;
        }
        
        let pred = this.head;
        for (let i = 0; i < index; i++) {
            pred = this.nodes.get(pred).next;
        }
        
        const succ = this.nodes.get(pred).next;
        const newNode = {};
        
        this.nodes.set(newNode, {
            val: val,
            prev: pred,
            next: succ
        });
        
        this.nodes.get(pred).next = newNode;
        this.nodes.get(succ).prev = newNode;
        
        this.size++;
    }
    
    addAtHead(val) {
        this.addAtIndex(0, val);
    }
    
    addAtTail(val) {
        this.addAtIndex(this.size, val);
    }
    
    deleteAtIndex(index) {
        if (index < 0 || index >= this.size) {
            return;
        }
        
        let pred = this.head;
        for (let i = 0; i < index; i++) {
            pred = this.nodes.get(pred).next;
        }
        
        const toDelete = this.nodes.get(pred).next;
        const succ = this.nodes.get(toDelete).next;
        
        this.nodes.get(pred).next = succ;
        this.nodes.get(succ).prev = pred;
        
        this.size--;
    }
}

// 链表操作函数
const linkedListOperations = (operations) => {
    const obj = new MyLinkedList();
    const results = [];
    
    operations.forEach(([op, ...params]) => {
        switch (op) {
            case 'get':
                results.push(obj.get(params[0]));
                break;
            case 'addAtHead':
                obj.addAtHead(params[0]);
                results.push(null);
                break;
            case 'addAtTail':
                obj.addAtTail(params[0]);
                results.push(null);
                break;
            case 'addAtIndex':
                obj.addAtIndex(params[0], params[1]);
                results.push(null);
                break;
            case 'deleteAtIndex':
                obj.deleteAtIndex(params[0]);
                results.push(null);
                break;
            default:
                results.push(null);
        }
    });
    
    return results;
};

// 使用高阶函数的链表操作
const createLinkedListOperator = () => {
    const list = new MyLinkedList();
    
    const operations = {
        get: (index) => list.get(index),
        addAtHead: (val) => { list.addAtHead(val); return null; },
        addAtTail: (val) => { list.addAtTail(val); return null; },
        addAtIndex: (index, val) => { list.addAtIndex(index, val); return null; },
        deleteAtIndex: (index) => { list.deleteAtIndex(index); return null; }
    };
    
    return (operationName, ...params) => {
        return operations[operationName]?.(...params) ?? null;
    };
};

// 链式操作的链表
class ChainableLinkedList {
    constructor() {
        this.list = new MyLinkedList();
    }
    
    get(index) {
        return this.list.get(index);
    }
    
    addAtHead(val) {
        this.list.addAtHead(val);
        return this; // 返回this支持链式调用
    }
    
    addAtTail(val) {
        this.list.addAtTail(val);
        return this;
    }
    
    addAtIndex(index, val) {
        this.list.addAtIndex(index, val);
        return this;
    }
    
    deleteAtIndex(index) {
        this.list.deleteAtIndex(index);
        return this;
    }
    
    toString() {
        return this.list.toString();
    }
}

// 测试函数
function testDesignLinkedList() {
    console.log('=== 设计链表测试 ===');
    
    // 测试双向链表实现
    console.log('\n--- 双向链表实现测试 ---');
    const list = new MyLinkedList();
    
    list.addAtHead(7);
    list.addAtHead(2);
    list.addAtHead(1);
    console.log(`添加头部元素后: ${list}`);
    
    list.addAtIndex(3, 0);
    console.log(`在索引3添加0后: ${list}`);
    
    list.deleteAtIndex(2);
    console.log(`删除索引2后: ${list}`);
    
    list.addAtHead(6);
    console.log(`添加头部6后: ${list}`);
    
    list.addAtTail(4);
    console.log(`添加尾部4后: ${list}`);
    
    console.log(`获取索引5: ${list.get(5)}`); // -1
    console.log(`获取索引3: ${list.get(3)}`); // 0
    console.log(`获取索引2: ${list.get(2)}`); // 2
    console.log(`获取索引0: ${list.get(0)}`); // 6
    
    list.deleteAtIndex(0);
    console.log(`删除索引0后，获取索引0: ${list.get(0)}`); // 1
    
    // 测试数组实现
    console.log('\n--- 数组实现测试 ---');
    const arrayList = new ArrayLinkedList();
    arrayList.addAtHead(1);
    arrayList.addAtTail(3);
    arrayList.addAtIndex(1, 2);
    console.log(`数组实现操作后: ${arrayList}`);
    console.log(`获取索引1: ${arrayList.get(1)}`); // 2
    
    arrayList.deleteAtIndex(1);
    console.log(`删除索引1后: ${arrayList}`);
    console.log(`获取索引1: ${arrayList.get(1)}`); // 3
    
    // 测试单链表实现
    console.log('\n--- 单链表实现测试 ---');
    const singlyList = new SinglyLinkedList();
    singlyList.addAtHead(1);
    singlyList.addAtTail(3);
    singlyList.addAtIndex(1, 2);
    console.log('单链表实现操作后: [1, 2, 3]');
    console.log(`获取索引1: ${singlyList.get(1)}`); // 2
    
    // 测试函数式实现
    console.log('\n--- 函数式实现测试 ---');
    const funcList = new FunctionalLinkedList();
    funcList.addAtHead(1);
    funcList.addAtTail(3);
    funcList.addAtIndex(1, 2);
    console.log(`函数式实现操作后: ${funcList}`);
    console.log(`获取索引1: ${funcList.get(1)}`); // 2
    
    // 测试Map实现
    console.log('\n--- Map实现测试 ---');
    const mapList = new MapLinkedList();
    mapList.addAtHead(1);
    mapList.addAtTail(3);
    mapList.addAtIndex(1, 2);
    console.log(`Map实现操作后: ${mapList}`);
    console.log(`获取索引1: ${mapList.get(1)}`); // 2
    
    // 测试WeakMap实现
    console.log('\n--- WeakMap实现测试 ---');
    const weakMapList = new WeakMapLinkedList();
    weakMapList.addAtHead(1);
    weakMapList.addAtTail(3);
    weakMapList.addAtIndex(1, 2);
    console.log('WeakMap实现操作后: [1, 2, 3]');
    console.log(`获取索引1: ${weakMapList.get(1)}`); // 2
    
    // 测试函数式操作
    console.log('\n--- 函数式操作测试 ---');
    const operations = [
        ['addAtHead', 7],
        ['addAtHead', 2],
        ['addAtHead', 1],
        ['addAtIndex', 3, 0],
        ['deleteAtIndex', 2],
        ['addAtHead', 6],
        ['addAtTail', 4],
        ['get', 4]
    ];
    
    const results = linkedListOperations(operations);
    console.log(`函数式操作结果: ${JSON.stringify(results)}`);
    
    // 测试高阶函数操作
    console.log('\n--- 高阶函数操作测试 ---');
    const operator = createLinkedListOperator();
    operator('addAtHead', 1);
    operator('addAtTail', 3);
    operator('addAtIndex', 1, 2);
    console.log(`高阶函数操作，获取索引1: ${operator('get', 1)}`); // 2
    
    // 测试链式操作
    console.log('\n--- 链式操作测试 ---');
    const chainList = new ChainableLinkedList();
    const result = chainList
        .addAtHead(1)
        .addAtTail(3)
        .addAtIndex(1, 2)
        .toString();
    console.log(`链式操作结果: ${result}`);
    console.log(`获取索引1: ${chainList.get(1)}`); // 2
    
    console.log('\n=== JavaScript特性说明 ===');
    console.log('1. 动态类型: 运行时类型检查');
    console.log('2. 原型链: 对象继承机制');
    console.log('3. 闭包: 函数作用域和变量捕获');
    console.log('4. 高阶函数: 函数作为参数和返回值');
    console.log('5. ES6类: 现代面向对象语法');
    console.log('6. 数组方法: 丰富的内置操作');
    console.log('7. Map/WeakMap: 键值对数据结构');
    console.log('8. 链式调用: 方法返回this支持链式操作');
}

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        MyLinkedList,
        ArrayLinkedList,
        SinglyLinkedList,
        FunctionalLinkedList,
        MapLinkedList,
        WeakMapLinkedList,
        ChainableLinkedList,
        linkedListOperations,
        createLinkedListOperator,
        testDesignLinkedList
    };
}

// 如果在浏览器环境中直接运行
if (typeof window !== 'undefined') {
    window.testDesignLinkedList = testDesignLinkedList;
}

// 如果在Node.js环境中直接运行
if (typeof require !== 'undefined' && require.main === module) {
    testDesignLinkedList();
}

/*
JavaScript实现特点:

1. **动态类型系统**:
   - 运行时类型检查
   - 灵活的变量类型
   - 类型转换

2. **原型链继承**:
   - 对象原型机制
   - 动态属性添加
   - 原型方法共享

3. **函数式编程**:
   - 函数是一等公民
   - 高阶函数
   - 闭包和作用域

4. **ES6+特性**:
   - 类语法糖
   - 箭头函数
   - 解构赋值
   - 扩展运算符

5. **内置数据结构**:
   - Array动态数组
   - Map/Set集合
   - WeakMap/WeakSet弱引用

6. **异步编程**:
   - Promise/async-await
   - 事件循环
   - 回调函数

算法复杂度:
- get: O(n)
- addAtHead: O(1)
- addAtTail: O(1)
- addAtIndex: O(n)
- deleteAtIndex: O(n)
- 空间复杂度: O(n)
*/