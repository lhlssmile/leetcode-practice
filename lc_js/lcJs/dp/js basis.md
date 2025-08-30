# JavaScript 基础知识

## 1. 数据类型

### 基本数据类型
```javascript
// 数字 - 整数和浮点数
let num = 42;
let float = 3.14;

// 字符串
let str = "Hello";
let str2 = 'World';
let template = `Value: ${num}`; // 模板字符串

// 布尔值
let isTrue = true;
let isFalse = false;

// undefined - 未定义的值
let undefinedVar;

// null - 空值
let nullVar = null;

// Symbol (ES6) - 唯一标识符
let sym = Symbol('description');

// BigInt (ES2020) - 大整数
let bigInt = 9007199254740991n;
```

### 引用数据类型
```javascript
// 对象
let obj = { name: "John", age: 30 };

// 数组
let arr = [1, 2, 3, 4, 5];

// 函数
let func = function() { return "Hello"; };

// 日期
let date = new Date();

// 正则表达式
let regex = /\d+/g;
```

### 类型检查
```javascript
// typeof 操作符
console.log(typeof 42);           // "number"
console.log(typeof "Hello");      // "string"
console.log(typeof true);         // "boolean"
console.log(typeof undefined);    // "undefined"
console.log(typeof null);         // "object" (这是一个历史遗留bug)
console.log(typeof {});           // "object"
console.log(typeof []);           // "object" (数组也是对象)
console.log(typeof function(){}); // "function"

// 数组检查
console.log(Array.isArray([]));   // true
console.log(Array.isArray({}));   // false
```

## 2. 变量声明

### var, let, const
```javascript
// var - 函数作用域，可重复声明，有变量提升
var x = 10;
var x = 20; // 允许重复声明

// let - 块级作用域，不可重复声明，无变量提升
let y = 10;
// let y = 20; // 错误：不能重复声明

// const - 块级作用域，不可重新赋值，必须初始化
const z = 10;
// z = 20; // 错误：常量不能重新赋值

// 对于对象和数组，const只保证引用不变，内容可变
const obj = { value: 10 };
obj.value = 20; // 这是允许的
// obj = {}; // 错误：不能重新赋值

const arr = [1, 2, 3];
arr.push(4); // 这是允许的
// arr = []; // 错误：不能重新赋值
```

## 3. 运算符

### 算术运算符
```javascript
let a = 10, b = 3;

console.log(a + b);  // 13 (加法)
console.log(a - b);  // 7 (减法)
console.log(a * b);  // 30 (乘法)
console.log(a / b);  // 3.3333... (除法)
console.log(a % b);  // 1 (取余)
console.log(a ** b); // 1000 (幂运算，ES2016)

// 自增和自减
let c = 5;
console.log(c++); // 5 (后置自增，先返回再加1)
console.log(c);   // 6
console.log(++c); // 7 (前置自增，先加1再返回)
```

### 比较运算符
```javascript
console.log(5 == 5);    // true (相等)
console.log(5 == "5");  // true (相等，会进行类型转换)
console.log(5 === 5);   // true (严格相等，类型和值都相等)
console.log(5 === "5"); // false (严格相等，类型不同)

console.log(5 != 8);    // true (不相等)
console.log(5 != "5");  // false (不相等，会进行类型转换)
console.log(5 !== "5"); // true (严格不相等)

console.log(5 > 3);     // true (大于)
console.log(5 >= 5);    // true (大于等于)
console.log(5 < 8);     // true (小于)
console.log(5 <= 5);    // true (小于等于)
```

### 逻辑运算符
```javascript
console.log(true && true);   // true (逻辑与)
console.log(true && false);  // false
console.log(true || false);  // true (逻辑或)
console.log(false || false); // false
console.log(!true);          // false (逻辑非)

// 短路求值
let d = 10;
let e = d > 5 && "大于5";  // "大于5"
let f = d < 5 && "小于5";  // false
let g = d > 5 || "不大于5"; // true
let h = d < 5 || "不小于5"; // "不小于5"

// 空值合并运算符 (ES2020)
let i = null;
let j = i ?? "默认值"; // "默认值"
```

## 4. 条件语句

### if-else
```javascript
let age = 18;

if (age >= 18) {
    console.log("成年人");
} else if (age >= 13) {
    console.log("青少年");
} else {
    console.log("儿童");
}
```

### switch
```javascript
let day = 2;
let dayName;

switch (day) {
    case 1:
        dayName = "星期一";
        break;
    case 2:
        dayName = "星期二";
        break;
    // ... 其他情况
    default:
        dayName = "未知";
}

console.log(dayName); // "星期二"
```

### 三元运算符
```javascript
let age = 20;
let status = age >= 18 ? "成年人" : "未成年";
console.log(status); // "成年人"
```

## 5. 循环和遍历

### for 循环
```javascript
// 基本for循环
for (let i = 0; i < 5; i++) {
    console.log(i); // 0, 1, 2, 3, 4
}

// 遍历数组
let arr = [10, 20, 30, 40, 50];
for (let i = 0; i < arr.length; i++) {
    console.log(arr[i]); // 10, 20, 30, 40, 50
}
```

### for...of (ES6)
```javascript
// 遍历数组元素
let arr = [10, 20, 30];
for (let value of arr) {
    console.log(value); // 10, 20, 30
}

// 遍历字符串
for (let char of "Hello") {
    console.log(char); // "H", "e", "l", "l", "o"
}
```

### for...in
```javascript
// 遍历对象属性
let person = { name: "John", age: 30, job: "Developer" };
for (let key in person) {
    console.log(key + ": " + person[key]);
    // "name: John", "age: 30", "job: Developer"
}

// 注意：for...in也可用于数组，但会遍历所有可枚举属性，包括原型链上的
// 不推荐用for...in遍历数组
```

### while 和 do-while
```javascript
// while循环
let i = 0;
while (i < 5) {
    console.log(i); // 0, 1, 2, 3, 4
    i++;
}

// do-while循环（至少执行一次）
let j = 0;
do {
    console.log(j); // 0, 1, 2, 3, 4
    j++;
} while (j < 5);
```

### forEach, map, filter, reduce
```javascript
let numbers = [1, 2, 3, 4, 5];

// forEach - 遍历数组
numbers.forEach(function(num) {
    console.log(num * 2); // 2, 4, 6, 8, 10
});

// map - 创建新数组
let doubled = numbers.map(function(num) {
    return num * 2;
});
console.log(doubled); // [2, 4, 6, 8, 10]

// filter - 过滤数组
let evens = numbers.filter(function(num) {
    return num % 2 === 0;
});
console.log(evens); // [2, 4]

// reduce - 累积计算
let sum = numbers.reduce(function(total, num) {
    return total + num;
}, 0);
console.log(sum); // 15 (1+2+3+4+5)

// 箭头函数简化写法
let doubled2 = numbers.map(num => num * 2);
let evens2 = numbers.filter(num => num % 2 === 0);
let sum2 = numbers.reduce((total, num) => total + num, 0);
```

## 6. 函数

### 函数声明和表达式
```javascript
// 函数声明
function greet(name) {
    return "Hello, " + name + "!";
}

// 函数表达式
let sayHello = function(name) {
    return "Hello, " + name + "!";
};

// 箭头函数 (ES6)
let greetArrow = (name) => {
    return "Hello, " + name + "!";
};

// 简化的箭头函数（单一表达式）
let greetShort = name => "Hello, " + name + "!";

console.log(greet("John")); // "Hello, John!"
```

### 默认参数和剩余参数
```javascript
// 默认参数 (ES6)
function greet(name = "Guest") {
    return "Hello, " + name + "!";
}
console.log(greet()); // "Hello, Guest!"

// 剩余参数 (ES6)
function sum(...numbers) {
    return numbers.reduce((total, num) => total + num, 0);
}
console.log(sum(1, 2, 3, 4)); // 10
```

### 闭包
```javascript
function createCounter() {
    let count = 0;
    return function() {
        return ++count;
    };
}

let counter = createCounter();
console.log(counter()); // 1
console.log(counter()); // 2
console.log(counter()); // 3
```

## 7. 数组操作

### 创建和访问数组
```javascript
// 创建数组
let fruits = ["Apple", "Banana", "Orange"];
let numbers = new Array(1, 2, 3, 4, 5);

// 访问元素
console.log(fruits[0]); // "Apple"
console.log(fruits[1]); // "Banana"

// 数组长度
console.log(fruits.length); // 3
```

### 常用数组方法
```javascript
let arr = [1, 2, 3];

// 添加/删除元素
arr.push(4);         // 在末尾添加元素: [1, 2, 3, 4]
arr.pop();           // 删除末尾元素: [1, 2, 3]
arr.unshift(0);      // 在开头添加元素: [0, 1, 2, 3]
arr.shift();         // 删除开头元素: [1, 2, 3]

// 查找元素
console.log(arr.indexOf(2));     // 1 (返回元素的索引，不存在则返回-1)
console.log(arr.includes(2));    // true (检查数组是否包含某元素)

// 截取和合并
let sliced = arr.slice(1, 2);    // [2] (从索引1开始，到索引2之前)
let removed = arr.splice(1, 1);   // 删除从索引1开始的1个元素: arr变为[1, 3], removed为[2]
let combined = [0].concat(arr);   // [0, 1, 3] (合并数组)

// 排序和反转
let nums = [3, 1, 4, 2];
nums.sort();                      // [1, 2, 3, 4] (默认按字符串排序)
nums.reverse();                   // [4, 3, 2, 1] (反转数组)

// 自定义排序
nums.sort((a, b) => a - b);      // 升序: [1, 2, 3, 4]
nums.sort((a, b) => b - a);      // 降序: [4, 3, 2, 1]
```

## 8. 对象操作

### 创建和访问对象
```javascript
// 对象字面量
let person = {
    name: "John",
    age: 30,
    job: "Developer",
    greet: function() {
        return "Hello, I'm " + this.name;
    }
};

// 访问属性
console.log(person.name);        // "John" (点表示法)
console.log(person["age"]);      // 30 (括号表示法)
console.log(person.greet());     // "Hello, I'm John" (调用方法)
```

### 对象方法
```javascript
let person = { name: "John", age: 30 };

// 获取所有键
console.log(Object.keys(person));   // ["name", "age"]

// 获取所有值
console.log(Object.values(person)); // ["John", 30]

// 获取所有键值对
console.log(Object.entries(person)); // [["name", "John"], ["age", 30]]

// 合并对象
let details = { job: "Developer", country: "USA" };
let fullPerson = Object.assign({}, person, details);
// 或使用扩展运算符 (ES6)
let fullPerson2 = { ...person, ...details };
```

## 9. 解构赋值 (ES6)

### 数组解构
```javascript
let [a, b, c] = [1, 2, 3];
console.log(a, b, c); // 1 2 3

// 跳过元素
let [x, , z] = [1, 2, 3];
console.log(x, z); // 1 3

// 剩余元素
let [first, ...rest] = [1, 2, 3, 4];
console.log(first, rest); // 1 [2, 3, 4]

// 默认值
let [p = 10, q = 20] = [1];
console.log(p, q); // 1 20
```

### 对象解构
```javascript
let person = { name: "John", age: 30, job: "Developer" };

// 基本解构
let { name, age } = person;
console.log(name, age); // "John" 30

// 重命名
let { name: personName, job: occupation } = person;
console.log(personName, occupation); // "John" "Developer"

// 默认值
let { name, salary = "未知" } = person;
console.log(name, salary); // "John" "未知"

// 嵌套解构
let company = { 
    name: "ABC Corp", 
    address: { city: "New York", country: "USA" } 
};
let { address: { city } } = company;
console.log(city); // "New York"
```

## 10. 常用于力扣题目的技巧

### 创建特定大小的数组
```javascript
// 创建长度为5，填充0的数组
let arr1 = new Array(5).fill(0);  // [0, 0, 0, 0, 0]

// 创建二维数组 (3x3，填充0)
let matrix = Array(3).fill().map(() => Array(3).fill(0));
// [
//   [0, 0, 0],
//   [0, 0, 0],
//   [0, 0, 0]
// ]
```

### 数组去重
```javascript
let arr = [1, 2, 2, 3, 4, 4, 5];
let unique = [...new Set(arr)];  // [1, 2, 3, 4, 5]
```

### 数字和字符串转换
```javascript
// 字符串转数字
let num1 = parseInt("42");      // 42
let num2 = Number("3.14");     // 3.14
let num3 = +"123";             // 123

// 数字转字符串
let str1 = 42 + "";           // "42"
let str2 = String(3.14);       // "3.14"
let str3 = (123).toString();   // "123"
```

### 字符和ASCII码转换
```javascript
// 字符转ASCII码
let code = "A".charCodeAt(0);  // 65

// ASCII码转字符
let char = String.fromCharCode(65);  // "A"
```

### 优先队列（最小堆/最大堆）
```javascript
// JavaScript没有内置的优先队列，可以使用数组模拟
// 最小堆（用于力扣中的优先队列问题）
class MinHeap {
    constructor() {
        this.heap = [];
    }
    
    getParentIndex(i) {
        return Math.floor((i - 1) / 2);
    }
    
    getLeftChildIndex(i) {
        return 2 * i + 1;
    }
    
    getRightChildIndex(i) {
        return 2 * i + 2;
    }
    
    swap(i1, i2) {
        [this.heap[i1], this.heap[i2]] = [this.heap[i2], this.heap[i1]];
    }
    
    heapifyUp(index) {
        let currentIndex = index || this.heap.length - 1;
        let parentIndex = this.getParentIndex(currentIndex);
        
        while (currentIndex > 0 && this.heap[parentIndex] > this.heap[currentIndex]) {
            this.swap(parentIndex, currentIndex);
            currentIndex = parentIndex;
            parentIndex = this.getParentIndex(currentIndex);
        }
    }
    
    heapifyDown(index = 0) {
        let currentIndex = index;
        let leftChildIndex = this.getLeftChildIndex(currentIndex);
        let rightChildIndex = this.getRightChildIndex(currentIndex);
        let size = this.heap.length;
        
        if (leftChildIndex < size && this.heap[leftChildIndex] < this.heap[currentIndex]) {
            currentIndex = leftChildIndex;
        }
        
        if (rightChildIndex < size && this.heap[rightChildIndex] < this.heap[currentIndex]) {
            currentIndex = rightChildIndex;
        }
        
        if (currentIndex !== index) {
            this.swap(index, currentIndex);
            this.heapifyDown(currentIndex);
        }
    }
    
    add(value) {
        this.heap.push(value);
        this.heapifyUp();
    }
    
    poll() {
        if (this.heap.length === 0) return null;
        if (this.heap.length === 1) return this.heap.pop();
        
        const min = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.heapifyDown();
        return min;
    }
    
    peek() {
        return this.heap.length > 0 ? this.heap[0] : null;
    }
    
    size() {
        return this.heap.length;
    }
}

// 使用示例
let minHeap = new MinHeap();
minHeap.add(5);
minHeap.add(3);
minHeap.add(8);
minHeap.add(1);
console.log(minHeap.poll()); // 1
console.log(minHeap.peek()); // 3
```

### Map和Set
```javascript
// Map - 键值对集合，键可以是任意类型
let map = new Map();
map.set("name", "John");
map.set(1, "number one");
map.set({}, "object");

console.log(map.get("name")); // "John"
console.log(map.has(1));      // true
map.delete(1);
console.log(map.size);        // 2

// 遍历Map
for (let [key, value] of map) {
    console.log(key + " = " + value);
}

// Set - 唯一值的集合
let set = new Set();
set.add(1);
set.add(2);
set.add(1); // 重复值不会被添加

console.log(set.has(1));   // true
console.log(set.size);     // 2
set.delete(1);

// 遍历Set
for (let value of set) {
    console.log(value);
}
```

## 11. 常见算法模板

### 二分查找
```javascript
function binarySearch(nums, target) {
    let left = 0;
    let right = nums.length - 1;
    
    while (left <= right) {
        let mid = Math.floor((left + right) / 2);
        
        if (nums[mid] === target) {
            return mid; // 找到目标，返回索引
        } else if (nums[mid] < target) {
            left = mid + 1; // 目标在右半部分
        } else {
            right = mid - 1; // 目标在左半部分
        }
    }
    
    return -1; // 未找到目标
}

// 使用示例
let nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];
console.log(binarySearch(nums, 5)); // 4
console.log(binarySearch(nums, 10)); // -1
```

### 深度优先搜索 (DFS)
```javascript
// 递归实现 (以二叉树为例)
function dfs(node) {
    if (!node) return;
    
    // 处理当前节点
    console.log(node.val);
    
    // 递归遍历左右子树
    dfs(node.left);
    dfs(node.right);
}

// 使用栈实现 (以图为例)
function dfsWithStack(graph, start) {
    let visited = new Set();
    let stack = [start];
    
    while (stack.length > 0) {
        let node = stack.pop();
        
        if (!visited.has(node)) {
            // 处理当前节点
            console.log(node);
            visited.add(node);
            
            // 将相邻节点加入栈
            for (let neighbor of graph[node]) {
                if (!visited.has(neighbor)) {
                    stack.push(neighbor);
                }
            }
        }
    }
}
```

### 广度优先搜索 (BFS)
```javascript
function bfs(graph, start) {
    let visited = new Set();
    let queue = [start];
    visited.add(start);
    
    while (queue.length > 0) {
        let node = queue.shift();
        
        // 处理当前节点
        console.log(node);
        
        // 将未访问的相邻节点加入队列
        for (let neighbor of graph[node]) {
            if (!visited.has(neighbor)) {
                visited.add(neighbor);
                queue.push(neighbor);
            }
        }
    }
}
```

### 动态规划模板
```javascript
// 斐波那契数列 (自底向上)
function fibonacci(n) {
    if (n <= 1) return n;
    
    let dp = new Array(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (let i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// 优化空间复杂度
function fibonacciOptimized(n) {
    if (n <= 1) return n;
    
    let prev = 0;
    let curr = 1;
    
    for (let i = 2; i <= n; i++) {
        let next = prev + curr;
        prev = curr;
        curr = next;
    }
    
    return curr;
}
```

### 回溯算法模板
```javascript
function backtrack(candidates, target) {
    let result = [];
    
    function dfs(start, target, path) {
        // 达到目标
        if (target === 0) {
            result.push([...path]);
            return;
        }
        
        // 超出目标或无法继续
        if (target < 0) return;
        
        for (let i = start; i < candidates.length; i++) {
            // 可以进行剪枝优化
            if (candidates[i] > target) continue;
            
            // 选择当前元素
            path.push(candidates[i]);
            
            // 递归
            dfs(i, target - candidates[i], path); // 允许重复使用元素，如果不允许则使用i+1
            
            // 回溯，撤销选择
            path.pop();
        }
    }
    
    dfs(0, target, []);
    return result;
}

// 使用示例 (组合总和问题)
let candidates = [2, 3, 6, 7];
let target = 7;
console.log(backtrack(candidates, target)); // [[2,2,3], [7]]
```