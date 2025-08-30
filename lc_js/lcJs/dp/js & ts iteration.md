# JavaScript 和 TypeScript 遍历方法总结

## 数组遍历

### 1. for 循环

```javascript
// JavaScript
const arr = [1, 2, 3, 4, 5];
for (let i = 0; i < arr.length; i++) {
    console.log(arr[i]);
}
```

```typescript
// TypeScript
const arr: number[] = [1, 2, 3, 4, 5];
for (let i = 0; i < arr.length; i++) {
    console.log(arr[i]);
}
```

**特点**：
- 最传统的遍历方式
- 可以访问索引
- 可以修改原数组
- 可以使用 break 和 continue
- 可以控制遍历方向和步长

### 2. for...of 循环

```javascript
// JavaScript
const arr = [1, 2, 3, 4, 5];
for (const item of arr) {
    console.log(item);
}
```

```typescript
// TypeScript
const arr: number[] = [1, 2, 3, 4, 5];
for (const item of arr) {
    console.log(item);
}
```

**特点**：
- ES6 新增语法
- 直接获取元素值
- 可以使用 break 和 continue
- 不能直接获取索引
- 适用于所有可迭代对象（Array, Map, Set, String 等）

### 3. forEach 方法

```javascript
// JavaScript
const arr = [1, 2, 3, 4, 5];
arr.forEach((item, index, array) => {
    console.log(item, index, array);
});
```

```typescript
// TypeScript
const arr: number[] = [1, 2, 3, 4, 5];
arr.forEach((item: number, index: number, array: number[]) => {
    console.log(item, index, array);
});
```

**特点**：
- 回调函数方式遍历
- 可以同时获取元素值和索引
- 不能使用 break 和 continue（可以用 return 跳过当前迭代）
- 不能提前终止循环
- 不会返回新数组

### 4. map 方法

```javascript
// JavaScript
const arr = [1, 2, 3, 4, 5];
const newArr = arr.map((item, index, array) => {
    return item * 2;
});
console.log(newArr); // [2, 4, 6, 8, 10]
```

```typescript
// TypeScript
const arr: number[] = [1, 2, 3, 4, 5];
const newArr: number[] = arr.map((item: number, index: number, array: number[]): number => {
    return item * 2;
});
console.log(newArr); // [2, 4, 6, 8, 10]
```

**特点**：
- 返回新数组，不修改原数组
- 数组长度保持不变
- 每个元素都会被回调函数处理
- 常用于数据转换

### 5. filter 方法

```javascript
// JavaScript
const arr = [1, 2, 3, 4, 5];
const filteredArr = arr.filter((item, index, array) => {
    return item > 2;
});
console.log(filteredArr); // [3, 4, 5]
```

```typescript
// TypeScript
const arr: number[] = [1, 2, 3, 4, 5];
const filteredArr: number[] = arr.filter((item: number, index: number, array: number[]): boolean => {
    return item > 2;
});
console.log(filteredArr); // [3, 4, 5]
```

**特点**：
- 返回新数组，不修改原数组
- 返回满足条件的元素
- 常用于数据筛选

### 6. reduce 方法

```javascript
// JavaScript
const arr = [1, 2, 3, 4, 5];
const sum = arr.reduce((accumulator, currentValue, index, array) => {
    return accumulator + currentValue;
}, 0);
console.log(sum); // 15
```

```typescript
// TypeScript
const arr: number[] = [1, 2, 3, 4, 5];
const sum: number = arr.reduce((accumulator: number, currentValue: number, index: number, array: number[]): number => {
    return accumulator + currentValue;
}, 0);
console.log(sum); // 15
```

**特点**：
- 将数组归约为单个值
- 可以指定初始值
- 非常灵活，可以实现很多复杂操作
- 常用于求和、求最大/最小值、数组扁平化等

### 7. some 和 every 方法

```javascript
// JavaScript
const arr = [1, 2, 3, 4, 5];

// some: 检查是否至少有一个元素满足条件
const hasEven = arr.some(item => item % 2 === 0);
console.log(hasEven); // true

// every: 检查是否所有元素都满足条件
const allEven = arr.every(item => item % 2 === 0);
console.log(allEven); // false
```

```typescript
// TypeScript
const arr: number[] = [1, 2, 3, 4, 5];

// some: 检查是否至少有一个元素满足条件
const hasEven: boolean = arr.some((item: number): boolean => item % 2 === 0);
console.log(hasEven); // true

// every: 检查是否所有元素都满足条件
const allEven: boolean = arr.every((item: number): boolean => item % 2 === 0);
console.log(allEven); // false
```

**特点**：
- 返回布尔值
- some: 有一个满足条件就返回 true
- every: 所有元素都满足条件才返回 true
- 可以提前终止循环（some 找到 true 就停止，every 找到 false 就停止）

### 8. find 和 findIndex 方法

```javascript
// JavaScript
const arr = [1, 2, 3, 4, 5];

// find: 返回第一个满足条件的元素
const found = arr.find(item => item > 3);
console.log(found); // 4

// findIndex: 返回第一个满足条件的元素的索引
const foundIndex = arr.findIndex(item => item > 3);
console.log(foundIndex); // 3
```

```typescript
// TypeScript
const arr: number[] = [1, 2, 3, 4, 5];

// find: 返回第一个满足条件的元素
const found: number | undefined = arr.find((item: number): boolean => item > 3);
console.log(found); // 4

// findIndex: 返回第一个满足条件的元素的索引
const foundIndex: number = arr.findIndex((item: number): boolean => item > 3);
console.log(foundIndex); // 3
```

**特点**：
- find 返回第一个满足条件的元素，没有则返回 undefined
- findIndex 返回第一个满足条件的元素的索引，没有则返回 -1
- 找到满足条件的元素后立即停止遍历

## 对象遍历

### 1. for...in 循环

```javascript
// JavaScript
const obj = { a: 1, b: 2, c: 3 };
for (const key in obj) {
    if (obj.hasOwnProperty(key)) { // 防止遍历原型链上的属性
        console.log(key, obj[key]);
    }
}
```

```typescript
// TypeScript
interface MyObject {
    [key: string]: number;
}

const obj: MyObject = { a: 1, b: 2, c: 3 };
for (const key in obj) {
    if (Object.prototype.hasOwnProperty.call(obj, key)) { // 更安全的写法
        console.log(key, obj[key]);
    }
}
```

**特点**：
- 遍历对象的可枚举属性（包括原型链上的属性）
- 通常需要使用 hasOwnProperty 过滤掉原型链上的属性
- 遍历顺序不一定是属性定义的顺序

### 2. Object.keys, Object.values, Object.entries

```javascript
// JavaScript
const obj = { a: 1, b: 2, c: 3 };

// Object.keys: 返回对象自身可枚举属性的键名数组
const keys = Object.keys(obj);
console.log(keys); // ['a', 'b', 'c']

// Object.values: 返回对象自身可枚举属性的值数组
const values = Object.values(obj);
console.log(values); // [1, 2, 3]

// Object.entries: 返回对象自身可枚举属性的键值对数组
const entries = Object.entries(obj);
console.log(entries); // [['a', 1], ['b', 2], ['c', 3]]

// 使用 forEach 遍历
Object.keys(obj).forEach(key => {
    console.log(key, obj[key]);
});

// 使用 for...of 遍历 entries
for (const [key, value] of Object.entries(obj)) {
    console.log(key, value);
}
```

```typescript
// TypeScript
interface MyObject {
    [key: string]: number;
}

const obj: MyObject = { a: 1, b: 2, c: 3 };

// Object.keys
const keys: string[] = Object.keys(obj);
console.log(keys); // ['a', 'b', 'c']

// Object.values
const values: number[] = Object.values(obj);
console.log(values); // [1, 2, 3]

// Object.entries
const entries: [string, number][] = Object.entries(obj);
console.log(entries); // [['a', 1], ['b', 2], ['c', 3]]

// 使用 forEach 遍历
Object.keys(obj).forEach((key: string) => {
    console.log(key, obj[key]);
});

// 使用 for...of 遍历 entries
for (const [key, value] of Object.entries(obj)) {
    console.log(key, value);
}
```

**特点**：
- 只遍历对象自身的可枚举属性，不包括原型链上的属性
- 返回数组，可以使用数组的方法进行进一步处理
- ES6+ 新增方法，更加简洁和安全

## Map 和 Set 遍历

### 1. Map 遍历

```javascript
// JavaScript
const map = new Map();
map.set('a', 1);
map.set('b', 2);
map.set('c', 3);

// 使用 forEach
map.forEach((value, key, map) => {
    console.log(key, value);
});

// 使用 for...of 遍历 entries
for (const [key, value] of map) { // map.entries() 可以省略
    console.log(key, value);
}

// 单独遍历键或值
for (const key of map.keys()) {
    console.log(key);
}

for (const value of map.values()) {
    console.log(value);
}
```

```typescript
// TypeScript
const map: Map<string, number> = new Map();
map.set('a', 1);
map.set('b', 2);
map.set('c', 3);

// 使用 forEach
map.forEach((value: number, key: string, map: Map<string, number>) => {
    console.log(key, value);
});

// 使用 for...of 遍历 entries
for (const [key, value] of map) { // map.entries() 可以省略
    console.log(key, value);
}

// 单独遍历键或值
for (const key of map.keys()) {
    console.log(key);
}

for (const value of map.values()) {
    console.log(value);
}
```

**特点**：
- Map 是有序的键值对集合
- 键可以是任意类型（包括对象）
- 提供了多种遍历方法：keys(), values(), entries()
- 遍历顺序与插入顺序一致

### 2. Set 遍历

```javascript
// JavaScript
const set = new Set([1, 2, 3, 4, 5]);

// 使用 forEach
set.forEach((value, sameValue, set) => { // 注意：第二个参数与第一个相同
    console.log(value);
});

// 使用 for...of
for (const value of set) {
    console.log(value);
}

// 使用 values() 方法（与 for...of 等价）
for (const value of set.values()) {
    console.log(value);
}

// 使用 keys() 方法（与 values() 等价，为了与 Map 接口一致）
for (const key of set.keys()) {
    console.log(key);
}

// 使用 entries() 方法（返回 [value, value] 对）
for (const [key, value] of set.entries()) {
    console.log(key, value); // key 和 value 相同
}
```

```typescript
// TypeScript
const set: Set<number> = new Set([1, 2, 3, 4, 5]);

// 使用 forEach
set.forEach((value: number, sameValue: number, set: Set<number>) => {
    console.log(value);
});

// 使用 for...of
for (const value of set) {
    console.log(value);
}

// 使用 values() 方法
for (const value of set.values()) {
    console.log(value);
}

// 使用 keys() 方法
for (const key of set.keys()) {
    console.log(key);
}

// 使用 entries() 方法
for (const [key, value] of set.entries()) {
    console.log(key, value);
}
```

**特点**：
- Set 是值的集合，没有键
- 值不能重复
- 提供了与 Map 类似的遍历方法，但 keys() 和 values() 返回相同的结果
- 遍历顺序与插入顺序一致

## 字符串遍历

```javascript
// JavaScript
const str = "Hello";

// 使用 for 循环
for (let i = 0; i < str.length; i++) {
    console.log(str[i]);
}

// 使用 for...of（可以正确处理 Unicode 字符）
for (const char of str) {
    console.log(char);
}

// 使用 split 和 forEach
str.split('').forEach(char => {
    console.log(char);
});

// 使用扩展运算符转为数组
[...str].forEach(char => {
    console.log(char);
});
```

```typescript
// TypeScript
const str: string = "Hello";

// 使用 for 循环
for (let i = 0; i < str.length; i++) {
    console.log(str[i]);
}

// 使用 for...of
for (const char of str) {
    console.log(char);
}

// 使用 split 和 forEach
str.split('').forEach((char: string) => {
    console.log(char);
});

// 使用扩展运算符转为数组
[...str].forEach((char: string) => {
    console.log(char);
});
```

**特点**：
- for...of 可以正确处理 Unicode 字符（如表情符号）
- 字符串是不可变的，不能通过索引修改字符

## LeetCode 常用遍历技巧

### 1. 二维数组/矩阵遍历

```javascript
// JavaScript
const matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];

// 常规遍历
for (let i = 0; i < matrix.length; i++) {
    for (let j = 0; j < matrix[i].length; j++) {
        console.log(matrix[i][j]);
    }
}

// 使用 forEach
matrix.forEach((row, i) => {
    row.forEach((value, j) => {
        console.log(value, i, j);
    });
});

// 四个方向遍历（常用于搜索、迷宫等问题）
const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]; // 右、下、左、上
const rows = matrix.length;
const cols = matrix[0].length;

function isValid(i, j) {
    return i >= 0 && i < rows && j >= 0 && j < cols;
}

function dfs(i, j, visited) {
    if (!isValid(i, j) || visited[i][j]) {
        return;
    }
    
    console.log(matrix[i][j]);
    visited[i][j] = true;
    
    for (const [di, dj] of directions) {
        dfs(i + di, j + dj, visited);
    }
}

// 调用 DFS
const visited = Array(rows).fill().map(() => Array(cols).fill(false));
dfs(0, 0, visited);
```

```typescript
// TypeScript
const matrix: number[][] = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];

// 常规遍历
for (let i = 0; i < matrix.length; i++) {
    for (let j = 0; j < matrix[i].length; j++) {
        console.log(matrix[i][j]);
    }
}

// 使用 forEach
matrix.forEach((row: number[], i: number) => {
    row.forEach((value: number, j: number) => {
        console.log(value, i, j);
    });
});

// 四个方向遍历
type Direction = [number, number];
const directions: Direction[] = [[0, 1], [1, 0], [0, -1], [-1, 0]]; // 右、下、左、上
const rows: number = matrix.length;
const cols: number = matrix[0].length;

function isValid(i: number, j: number): boolean {
    return i >= 0 && i < rows && j >= 0 && j < cols;
}

function dfs(i: number, j: number, visited: boolean[][]): void {
    if (!isValid(i, j) || visited[i][j]) {
        return;
    }
    
    console.log(matrix[i][j]);
    visited[i][j] = true;
    
    for (const [di, dj] of directions) {
        dfs(i + di, j + dj, visited);
    }
}

// 调用 DFS
const visited: boolean[][] = Array(rows).fill(null).map(() => Array(cols).fill(false));
dfs(0, 0, visited);
```

### 2. 链表遍历

```javascript
// JavaScript
class ListNode {
    constructor(val = 0, next = null) {
        this.val = val;
        this.next = next;
    }
}

// 创建链表: 1->2->3->4->5
const head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
head.next.next.next = new ListNode(4);
head.next.next.next.next = new ListNode(5);

// 迭代遍历
function traverseIterative(head) {
    let current = head;
    while (current !== null) {
        console.log(current.val);
        current = current.next;
    }
}

// 递归遍历
function traverseRecursive(node) {
    if (node === null) {
        return;
    }
    console.log(node.val);
    traverseRecursive(node.next);
}

// 快慢指针（常用于检测环、找中点等）
function findMiddle(head) {
    if (!head || !head.next) {
        return head;
    }
    
    let slow = head;
    let fast = head;
    
    while (fast && fast.next) {
        slow = slow.next;
        fast = fast.next.next;
    }
    
    return slow; // 中间节点
}

traverseIterative(head);
traverseRecursive(head);
console.log("Middle node value:", findMiddle(head).val);
```

```typescript
// TypeScript
class ListNode {
    val: number;
    next: ListNode | null;
    
    constructor(val: number = 0, next: ListNode | null = null) {
        this.val = val;
        this.next = next;
    }
}

// 创建链表: 1->2->3->4->5
const head: ListNode = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
head.next.next.next = new ListNode(4);
head.next.next.next.next = new ListNode(5);

// 迭代遍历
function traverseIterative(head: ListNode | null): void {
    let current: ListNode | null = head;
    while (current !== null) {
        console.log(current.val);
        current = current.next;
    }
}

// 递归遍历
function traverseRecursive(node: ListNode | null): void {
    if (node === null) {
        return;
    }
    console.log(node.val);
    traverseRecursive(node.next);
}

// 快慢指针
function findMiddle(head: ListNode | null): ListNode | null {
    if (!head || !head.next) {
        return head;
    }
    
    let slow: ListNode = head;
    let fast: ListNode | null = head;
    
    while (fast && fast.next) {
        slow = slow.next!;
        fast = fast.next.next;
    }
    
    return slow;
}

traverseIterative(head);
traverseRecursive(head);
console.log("Middle node value:", findMiddle(head)?.val);
```

### 3. 树的遍历

```javascript
// JavaScript
class TreeNode {
    constructor(val = 0, left = null, right = null) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

// 创建二叉树
const root = new TreeNode(1);
root.left = new TreeNode(2);
root.right = new TreeNode(3);
root.left.left = new TreeNode(4);
root.left.right = new TreeNode(5);

// 前序遍历（根-左-右）
function preorderTraversal(root) {
    const result = [];
    
    function dfs(node) {
        if (node === null) {
            return;
        }
        
        result.push(node.val); // 访问根节点
        dfs(node.left);        // 遍历左子树
        dfs(node.right);       // 遍历右子树
    }
    
    dfs(root);
    return result;
}

// 中序遍历（左-根-右）
function inorderTraversal(root) {
    const result = [];
    
    function dfs(node) {
        if (node === null) {
            return;
        }
        
        dfs(node.left);        // 遍历左子树
        result.push(node.val); // 访问根节点
        dfs(node.right);       // 遍历右子树
    }
    
    dfs(root);
    return result;
}

// 后序遍历（左-右-根）
function postorderTraversal(root) {
    const result = [];
    
    function dfs(node) {
        if (node === null) {
            return;
        }
        
        dfs(node.left);        // 遍历左子树
        dfs(node.right);       // 遍历右子树
        result.push(node.val); // 访问根节点
    }
    
    dfs(root);
    return result;
}

// 层序遍历（BFS）
function levelOrderTraversal(root) {
    if (root === null) {
        return [];
    }
    
    const result = [];
    const queue = [root];
    
    while (queue.length > 0) {
        const levelSize = queue.length;
        const currentLevel = [];
        
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            currentLevel.push(node.val);
            
            if (node.left) {
                queue.push(node.left);
            }
            
            if (node.right) {
                queue.push(node.right);
            }
        }
        
        result.push(currentLevel);
    }
    
    return result;
}

console.log("Preorder:", preorderTraversal(root));
console.log("Inorder:", inorderTraversal(root));
console.log("Postorder:", postorderTraversal(root));
console.log("Level order:", levelOrderTraversal(root));
```

```typescript
// TypeScript
class TreeNode {
    val: number;
    left: TreeNode | null;
    right: TreeNode | null;
    
    constructor(val: number = 0, left: TreeNode | null = null, right: TreeNode | null = null) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

// 创建二叉树
const root: TreeNode = new TreeNode(1);
root.left = new TreeNode(2);
root.right = new TreeNode(3);
root.left.left = new TreeNode(4);
root.left.right = new TreeNode(5);

// 前序遍历
function preorderTraversal(root: TreeNode | null): number[] {
    const result: number[] = [];
    
    function dfs(node: TreeNode | null): void {
        if (node === null) {
            return;
        }
        
        result.push(node.val);
        dfs(node.left);
        dfs(node.right);
    }
    
    dfs(root);
    return result;
}

// 中序遍历
function inorderTraversal(root: TreeNode | null): number[] {
    const result: number[] = [];
    
    function dfs(node: TreeNode | null): void {
        if (node === null) {
            return;
        }
        
        dfs(node.left);
        result.push(node.val);
        dfs(node.right);
    }
    
    dfs(root);
    return result;
}

// 后序遍历
function postorderTraversal(root: TreeNode | null): number[] {
    const result: number[] = [];
    
    function dfs(node: TreeNode | null): void {
        if (node === null) {
            return;
        }
        
        dfs(node.left);
        dfs(node.right);
        result.push(node.val);
    }
    
    dfs(root);
    return result;
}

// 层序遍历
function levelOrderTraversal(root: TreeNode | null): number[][] {
    if (root === null) {
        return [];
    }
    
    const result: number[][] = [];
    const queue: TreeNode[] = [root];
    
    while (queue.length > 0) {
        const levelSize: number = queue.length;
        const currentLevel: number[] = [];
        
        for (let i = 0; i < levelSize; i++) {
            const node: TreeNode = queue.shift()!;
            currentLevel.push(node.val);
            
            if (node.left) {
                queue.push(node.left);
            }
            
            if (node.right) {
                queue.push(node.right);
            }
        }
        
        result.push(currentLevel);
    }
    
    return result;
}

console.log("Preorder:", preorderTraversal(root));
console.log("Inorder:", inorderTraversal(root));
console.log("Postorder:", postorderTraversal(root));
console.log("Level order:", levelOrderTraversal(root));
```

## 总结

### JavaScript 遍历方法选择指南

1. **数组遍历**：
   - 需要索引：for 循环或 forEach
   - 需要 break/continue：for 循环或 for...of
   - 需要转换元素：map
   - 需要筛选元素：filter
   - 需要累积计算：reduce
   - 需要查找元素：find/findIndex
   - 需要判断条件：some/every

2. **对象遍历**：
   - 传统方式：for...in + hasOwnProperty
   - 现代方式：Object.keys/values/entries + forEach 或 for...of

3. **Map/Set 遍历**：
   - 首选：for...of 或 forEach

4. **特殊数据结构**：
   - 链表：while 循环或递归
   - 树：递归（DFS）或队列（BFS）
   - 图：邻接表/邻接矩阵 + DFS/BFS

### TypeScript 额外注意点

1. **类型声明**：
   - 为数组、对象、回调函数等添加适当的类型
   - 使用泛型提高代码复用性
   - 使用接口定义复杂数据结构

2. **空值处理**：
   - 使用可选链操作符（?.）和空值合并操作符（??）
   - 使用类型守卫（type guards）确保类型安全

3. **高级类型**：
   - 使用联合类型（|）和交叉类型（&）
   - 使用类型断言（as）在必要时指定类型