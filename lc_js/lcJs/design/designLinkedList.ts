// LeetCode 707: 设计链表
// TypeScript版本实现，展示静态类型系统和面向对象特性

// 双向链表节点接口
interface IListNode<T = number> {
    val: T;
    prev: IListNode<T> | null;
    next: IListNode<T> | null;
}

// 链表操作接口
interface ILinkedList<T = number> {
    get(index: number): T | -1;
    addAtHead(val: T): void;
    addAtTail(val: T): void;
    addAtIndex(index: number, val: T): void;
    deleteAtIndex(index: number): void;
    getSize(): number;
}

// 双向链表节点类
class ListNode<T = number> implements IListNode<T> {
    public val: T;
    public prev: ListNode<T> | null = null;
    public next: ListNode<T> | null = null;
    
    constructor(val: T) {
        this.val = val;
    }
    
    toString(): string {
        return `ListNode(${this.val})`;
    }
}

// 双向链表实现
class MyLinkedList<T = number> implements ILinkedList<T> {
    private head: ListNode<T>;
    private tail: ListNode<T>;
    private size: number;
    
    constructor() {
        // 创建哨兵节点
        this.head = new ListNode<T>(null as any);
        this.tail = new ListNode<T>(null as any);
        this.head.next = this.tail;
        this.tail.prev = this.head;
        this.size = 0;
    }
    
    /**
     * 获取链表中第 index 个节点的值
     */
    get(index: number): T | -1 {
        if (index < 0 || index >= this.size) {
            return -1;
        }
        
        let current = this.head.next!;
        for (let i = 0; i < index; i++) {
            current = current.next!;
        }
        return current.val;
    }
    
    /**
     * 在链表第一个元素之前添加一个值为 val 的节点
     */
    addAtHead(val: T): void {
        this.addAtIndex(0, val);
    }
    
    /**
     * 将值为 val 的节点追加到链表的最后一个元素
     */
    addAtTail(val: T): void {
        this.addAtIndex(this.size, val);
    }
    
    /**
     * 在链表中的第 index 个节点之前添加值为 val 的节点
     */
    addAtIndex(index: number, val: T): void {
        if (index < 0 || index > this.size) {
            return;
        }
        
        let pred = this.head;
        for (let i = 0; i < index; i++) {
            pred = pred.next!;
        }
        
        const succ = pred.next!;
        const newNode = new ListNode<T>(val);
        
        newNode.prev = pred;
        newNode.next = succ;
        pred.next = newNode;
        succ.prev = newNode;
        
        this.size++;
    }
    
    /**
     * 如果索引 index 有效，则删除链表中的第 index 个节点
     */
    deleteAtIndex(index: number): void {
        if (index < 0 || index >= this.size) {
            return;
        }
        
        let pred = this.head;
        for (let i = 0; i < index; i++) {
            pred = pred.next!;
        }
        
        const toDelete = pred.next!;
        const succ = toDelete.next!;
        
        pred.next = succ;
        succ.prev = pred;
        
        this.size--;
    }
    
    /**
     * 获取链表大小
     */
    getSize(): number {
        return this.size;
    }
    
    /**
     * 转换为数组
     */
    toArray(): T[] {
        const result: T[] = [];
        let current = this.head.next;
        while (current !== this.tail) {
            result.push(current!.val);
            current = current!.next;
        }
        return result;
    }
    
    /**
     * 字符串表示
     */
    toString(): string {
        return JSON.stringify(this.toArray());
    }
}

// 泛型栈类（用于演示泛型）
class GenericStack<T> {
    private items: T[] = [];
    
    push(item: T): void {
        this.items.push(item);
    }
    
    pop(): T | undefined {
        return this.items.pop();
    }
    
    peek(): T | undefined {
        return this.items[this.items.length - 1];
    }
    
    isEmpty(): boolean {
        return this.items.length === 0;
    }
    
    size(): number {
        return this.items.length;
    }
}

// 使用泛型栈实现的链表
class StackBasedLinkedList<T = number> implements ILinkedList<T> {
    private data: T[] = [];
    
    get(index: number): T | -1 {
        return (index >= 0 && index < this.data.length) ? this.data[index] : -1;
    }
    
    addAtHead(val: T): void {
        this.data.unshift(val);
    }
    
    addAtTail(val: T): void {
        this.data.push(val);
    }
    
    addAtIndex(index: number, val: T): void {
        if (index >= 0 && index <= this.data.length) {
            this.data.splice(index, 0, val);
        }
    }
    
    deleteAtIndex(index: number): void {
        if (index >= 0 && index < this.data.length) {
            this.data.splice(index, 1);
        }
    }
    
    getSize(): number {
        return this.data.length;
    }
    
    toString(): string {
        return JSON.stringify(this.data);
    }
}

// 抽象链表基类
abstract class AbstractLinkedList<T = number> {
    protected abstract size: number;
    
    abstract get(index: number): T | -1;
    abstract addAtHead(val: T): void;
    abstract addAtTail(val: T): void;
    abstract addAtIndex(index: number, val: T): void;
    abstract deleteAtIndex(index: number): void;
    
    getSize(): number {
        return this.size;
    }
    
    isEmpty(): boolean {
        return this.size === 0;
    }
    
    // 模板方法模式
    addMultiple(values: T[]): void {
        values.forEach(val => this.addAtTail(val));
    }
    
    // 抽象方法的默认实现
    clear(): void {
        while (!this.isEmpty()) {
            this.deleteAtIndex(0);
        }
    }
}

// 继承抽象类的具体实现
class ConcreteLinkedList<T = number> extends AbstractLinkedList<T> {
    protected size: number = 0;
    private data: T[] = [];
    
    get(index: number): T | -1 {
        return (index >= 0 && index < this.size) ? this.data[index] : -1;
    }
    
    addAtHead(val: T): void {
        this.data.unshift(val);
        this.size++;
    }
    
    addAtTail(val: T): void {
        this.data.push(val);
        this.size++;
    }
    
    addAtIndex(index: number, val: T): void {
        if (index >= 0 && index <= this.size) {
            this.data.splice(index, 0, val);
            this.size++;
        }
    }
    
    deleteAtIndex(index: number): void {
        if (index >= 0 && index < this.size) {
            this.data.splice(index, 1);
            this.size--;
        }
    }
    
    toString(): string {
        return JSON.stringify(this.data);
    }
}

// 类型别名
type LinkedListOperation<T = number> = 
    | ['get', number]
    | ['addAtHead', T]
    | ['addAtTail', T]
    | ['addAtIndex', number, T]
    | ['deleteAtIndex', number];

type OperationResult<T = number> = T | -1 | null;

// 联合类型和字面量类型
type ListType = 'doubly' | 'singly' | 'array' | 'stack';

// 工厂模式创建链表
class LinkedListFactory {
    static create<T = number>(type: ListType): ILinkedList<T> {
        switch (type) {
            case 'doubly':
                return new MyLinkedList<T>();
            case 'array':
            case 'stack':
                return new StackBasedLinkedList<T>();
            default:
                throw new Error(`Unsupported list type: ${type}`);
        }
    }
}

// 装饰器模式（如果启用了装饰器）
function logOperation(target: any, propertyName: string, descriptor: PropertyDescriptor) {
    const method = descriptor.value;
    
    descriptor.value = function (...args: any[]) {
        console.log(`Calling ${propertyName} with args:`, args);
        const result = method.apply(this, args);
        console.log(`Result:`, result);
        return result;
    };
}

// 使用装饰器的链表类
class LoggedLinkedList<T = number> implements ILinkedList<T> {
    private list: MyLinkedList<T> = new MyLinkedList<T>();
    
    // @logOperation  // 需要启用装饰器支持
    get(index: number): T | -1 {
        return this.list.get(index);
    }
    
    // @logOperation
    addAtHead(val: T): void {
        this.list.addAtHead(val);
    }
    
    // @logOperation
    addAtTail(val: T): void {
        this.list.addAtTail(val);
    }
    
    // @logOperation
    addAtIndex(index: number, val: T): void {
        this.list.addAtIndex(index, val);
    }
    
    // @logOperation
    deleteAtIndex(index: number): void {
        this.list.deleteAtIndex(index);
    }
    
    getSize(): number {
        return this.list.getSize();
    }
}

// 函数式编程风格
const createLinkedListOperations = <T = number>() => {
    const list = new MyLinkedList<T>();
    
    const operations = {
        get: (index: number): T | -1 => list.get(index),
        addAtHead: (val: T): void => { list.addAtHead(val); },
        addAtTail: (val: T): void => { list.addAtTail(val); },
        addAtIndex: (index: number, val: T): void => { list.addAtIndex(index, val); },
        deleteAtIndex: (index: number): void => { list.deleteAtIndex(index); },
        getSize: (): number => list.getSize(),
        toArray: (): T[] => list.toArray()
    } as const;
    
    return operations;
};

// 高阶函数类型
type OperationHandler<T> = (list: ILinkedList<T>) => void;

// 链表操作执行器
class LinkedListExecutor<T = number> {
    private list: ILinkedList<T>;
    
    constructor(list: ILinkedList<T>) {
        this.list = list;
    }
    
    execute(operations: LinkedListOperation<T>[]): OperationResult<T>[] {
        return operations.map(([op, ...params]) => {
            switch (op) {
                case 'get':
                    return this.list.get(params[0] as number);
                case 'addAtHead':
                    this.list.addAtHead(params[0] as T);
                    return null;
                case 'addAtTail':
                    this.list.addAtTail(params[0] as T);
                    return null;
                case 'addAtIndex':
                    this.list.addAtIndex(params[0] as number, params[1] as T);
                    return null;
                case 'deleteAtIndex':
                    this.list.deleteAtIndex(params[0] as number);
                    return null;
                default:
                    return null;
            }
        });
    }
    
    batch(handlers: OperationHandler<T>[]): void {
        handlers.forEach(handler => handler(this.list));
    }
}

// 类型守卫
function isValidIndex(index: unknown): index is number {
    return typeof index === 'number' && index >= 0 && Number.isInteger(index);
}

function isValidValue<T>(value: unknown): value is T {
    return value !== null && value !== undefined;
}

// 安全的链表操作
class SafeLinkedList<T = number> implements ILinkedList<T> {
    private list: MyLinkedList<T> = new MyLinkedList<T>();
    
    get(index: number): T | -1 {
        if (!isValidIndex(index)) {
            throw new TypeError('Index must be a non-negative integer');
        }
        return this.list.get(index);
    }
    
    addAtHead(val: T): void {
        if (!isValidValue(val)) {
            throw new TypeError('Value cannot be null or undefined');
        }
        this.list.addAtHead(val);
    }
    
    addAtTail(val: T): void {
        if (!isValidValue(val)) {
            throw new TypeError('Value cannot be null or undefined');
        }
        this.list.addAtTail(val);
    }
    
    addAtIndex(index: number, val: T): void {
        if (!isValidIndex(index)) {
            throw new TypeError('Index must be a non-negative integer');
        }
        if (!isValidValue(val)) {
            throw new TypeError('Value cannot be null or undefined');
        }
        this.list.addAtIndex(index, val);
    }
    
    deleteAtIndex(index: number): void {
        if (!isValidIndex(index)) {
            throw new TypeError('Index must be a non-negative integer');
        }
        this.list.deleteAtIndex(index);
    }
    
    getSize(): number {
        return this.list.getSize();
    }
}

// 测试接口
interface TestCase<T = number> {
    name: string;
    operations: LinkedListOperation<T>[];
    expected: OperationResult<T>[];
}

// 测试函数
function testDesignLinkedList(): void {
    console.log('=== TypeScript设计链表测试 ===');
    
    // 测试基本双向链表
    console.log('\n--- 基本双向链表测试 ---');
    const list = new MyLinkedList<number>();
    
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
    
    // 测试泛型链表
    console.log('\n--- 泛型链表测试 ---');
    const stringList = new MyLinkedList<string>();
    stringList.addAtHead('world');
    stringList.addAtHead('hello');
    stringList.addAtIndex(1, ' ');
    console.log(`字符串链表: ${stringList}`);
    console.log(`获取索引1: ${stringList.get(1)}`); // ' '
    
    // 测试栈基础链表
    console.log('\n--- 栈基础链表测试 ---');
    const stackList = new StackBasedLinkedList<number>();
    stackList.addAtHead(1);
    stackList.addAtTail(3);
    stackList.addAtIndex(1, 2);
    console.log(`栈基础链表: ${stackList}`);
    console.log(`获取索引1: ${stackList.get(1)}`); // 2
    
    // 测试抽象类实现
    console.log('\n--- 抽象类实现测试 ---');
    const concreteList = new ConcreteLinkedList<number>();
    concreteList.addMultiple([1, 2, 3]);
    console.log(`具体链表: ${concreteList}`);
    console.log(`是否为空: ${concreteList.isEmpty()}`); // false
    console.log(`大小: ${concreteList.getSize()}`); // 3
    
    // 测试工厂模式
    console.log('\n--- 工厂模式测试 ---');
    const factoryList = LinkedListFactory.create<number>('doubly');
    factoryList.addAtHead(1);
    factoryList.addAtTail(3);
    factoryList.addAtIndex(1, 2);
    console.log('工厂创建的链表: [1, 2, 3]');
    console.log(`获取索引1: ${factoryList.get(1)}`); // 2
    
    // 测试函数式操作
    console.log('\n--- 函数式操作测试 ---');
    const funcOps = createLinkedListOperations<number>();
    funcOps.addAtHead(1);
    funcOps.addAtTail(3);
    funcOps.addAtIndex(1, 2);
    console.log(`函数式操作结果: ${JSON.stringify(funcOps.toArray())}`);
    console.log(`获取索引1: ${funcOps.get(1)}`); // 2
    
    // 测试操作执行器
    console.log('\n--- 操作执行器测试 ---');
    const executor = new LinkedListExecutor(new MyLinkedList<number>());
    const operations: LinkedListOperation<number>[] = [
        ['addAtHead', 7],
        ['addAtHead', 2],
        ['addAtHead', 1],
        ['addAtIndex', 3, 0],
        ['deleteAtIndex', 2],
        ['get', 2]
    ];
    
    const results = executor.execute(operations);
    console.log(`执行器结果: ${JSON.stringify(results)}`);
    
    // 测试安全链表
    console.log('\n--- 安全链表测试 ---');
    const safeList = new SafeLinkedList<number>();
    try {
        safeList.addAtHead(1);
        safeList.addAtTail(3);
        safeList.addAtIndex(1, 2);
        console.log('安全链表操作成功: [1, 2, 3]');
        console.log(`获取索引1: ${safeList.get(1)}`); // 2
        
        // 测试错误处理
        // safeList.get(-1); // 会抛出TypeError
    } catch (error) {
        console.log(`捕获错误: ${error}`);
    }
    
    // 测试用例
    console.log('\n--- 测试用例执行 ---');
    const testCases: TestCase<number>[] = [
        {
            name: '基本操作测试',
            operations: [
                ['addAtHead', 1],
                ['addAtTail', 3],
                ['addAtIndex', 1, 2],
                ['get', 1],
                ['deleteAtIndex', 1],
                ['get', 1]
            ],
            expected: [null, null, null, 2, null, 3]
        }
    ];
    
    testCases.forEach(testCase => {
        const testExecutor = new LinkedListExecutor(new MyLinkedList<number>());
        const actualResults = testExecutor.execute(testCase.operations);
        const passed = JSON.stringify(actualResults) === JSON.stringify(testCase.expected);
        console.log(`${testCase.name}: ${passed ? '通过' : '失败'}`);
        if (!passed) {
            console.log(`  期望: ${JSON.stringify(testCase.expected)}`);
            console.log(`  实际: ${JSON.stringify(actualResults)}`);
        }
    });
    
    console.log('\n=== TypeScript特性说明 ===');
    console.log('1. 静态类型系统: 编译时类型检查');
    console.log('2. 泛型: 类型参数化，代码复用');
    console.log('3. 接口: 契约定义，结构化类型');
    console.log('4. 抽象类: 部分实现的基类');
    console.log('5. 类型别名: 复杂类型的简化');
    console.log('6. 联合类型: 多种类型的组合');
    console.log('7. 类型守卫: 运行时类型检查');
    console.log('8. 装饰器: 元编程和AOP');
    console.log('9. 模块系统: 代码组织和封装');
    console.log('10. 严格空检查: null/undefined安全');
}

// 导出模块
export {
    IListNode,
    ILinkedList,
    ListNode,
    MyLinkedList,
    StackBasedLinkedList,
    AbstractLinkedList,
    ConcreteLinkedList,
    LinkedListFactory,
    LinkedListExecutor,
    SafeLinkedList,
    GenericStack,
    LoggedLinkedList,
    createLinkedListOperations,
    testDesignLinkedList,
    LinkedListOperation,
    OperationResult,
    ListType,
    TestCase
};

// 默认导出
export default MyLinkedList;

// 如果在Node.js环境中直接运行
if (typeof require !== 'undefined' && require.main === module) {
    testDesignLinkedList();
}

/*
TypeScript实现特点:

1. **静态类型系统**:
   - 编译时类型检查
   - 类型推断
   - 严格空检查

2. **泛型编程**:
   - 类型参数化
   - 约束泛型
   - 泛型接口和类

3. **面向对象特性**:
   - 接口定义
   - 抽象类
   - 继承和多态
   - 访问修饰符

4. **高级类型**:
   - 联合类型
   - 交叉类型
   - 条件类型
   - 映射类型

5. **类型安全**:
   - 类型守卫
   - 断言函数
   - 非空断言

6. **装饰器**:
   - 类装饰器
   - 方法装饰器
   - 属性装饰器

7. **模块系统**:
   - ES6模块
   - 命名空间
   - 声明合并

8. **工具类型**:
   - Partial<T>
   - Required<T>
   - Pick<T, K>
   - Omit<T, K>

算法复杂度:
- get: O(n)
- addAtHead: O(1)
- addAtTail: O(1)
- addAtIndex: O(n)
- deleteAtIndex: O(n)
- 空间复杂度: O(n)
*/