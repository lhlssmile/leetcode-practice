# TypeScript 基础知识

## 1. 基本类型

```typescript
// 基本类型注解
let isDone: boolean = false;
let decimal: number = 6;
let color: string = "blue";
let list: number[] = [1, 2, 3];
let list2: Array<number> = [1, 2, 3]; // 泛型数组类型

// 元组 Tuple - 允许表示一个已知元素数量和类型的数组
let x: [string, number] = ["hello", 10];

// 枚举 Enum
enum Color {Red, Green, Blue}
let c: Color = Color.Green; // 1

// Any - 不确定类型时使用
let notSure: any = 4;
notSure = "maybe a string";
notSure = false;

// Void - 没有任何类型，通常用于函数返回值
function warnUser(): void {
    console.log("This is a warning message");
}

// Null 和 Undefined
let u: undefined = undefined;
let n: null = null;

// Never - 永不存在的值的类型
function error(message: string): never {
    throw new Error(message);
}
```

## 2. 接口

```typescript
// 对象接口
interface Person {
    firstName: string;
    lastName: string;
    age?: number; // 可选属性
    readonly id: number; // 只读属性
}

function greet(person: Person) {
    return `Hello, ${person.firstName} ${person.lastName}`;
}

let user: Person = {
    firstName: "John",
    lastName: "Doe",
    id: 1
};

// 函数接口
interface SearchFunc {
    (source: string, subString: string): boolean;
}

let mySearch: SearchFunc = function(src, sub) {
    return src.search(sub) > -1;
};

// 可索引类型
interface StringArray {
    [index: number]: string;
}

let myArray: StringArray = ["Bob", "Fred"];
```

## 3. 类

```typescript
class Animal {
    private name: string;
    
    constructor(name: string) {
        this.name = name;
    }
    
    move(distanceInMeters: number = 0) {
        console.log(`${this.name} moved ${distanceInMeters}m.`);
    }
}

class Dog extends Animal {
    constructor(name: string) {
        super(name);
    }
    
    bark() {
        console.log('Woof! Woof!');
    }
    
    move(distanceInMeters = 5) {
        console.log('Running...');
        super.move(distanceInMeters);
    }
}

let dog = new Dog("Rex");
dog.bark();
dog.move(10);
```

## 4. 函数

```typescript
// 函数类型
function add(x: number, y: number): number {
    return x + y;
}

// 可选参数和默认参数
function buildName(firstName: string, lastName?: string): string {
    return lastName ? firstName + " " + lastName : firstName;
}

function buildName2(firstName: string, lastName = "Smith"): string {
    return firstName + " " + lastName;
}

// 剩余参数
function buildName3(firstName: string, ...restOfName: string[]): string {
    return firstName + " " + restOfName.join(" ");
}

// 函数重载
function padLeft(value: string, padding: string): string;
function padLeft(value: string, padding: number): string;
function padLeft(value: string, padding: string | number): string {
    if (typeof padding === "number") {
        return Array(padding + 1).join(" ") + value;
    }
    if (typeof padding === "string") {
        return padding + value;
    }
    throw new Error(`Expected string or number, got '${padding}'.`);
}
```

## 5. 泛型

```typescript
// 泛型函数
function identity<T>(arg: T): T {
    return arg;
}

let output = identity<string>("myString");
let output2 = identity("myString"); // 类型推断

// 泛型接口
interface GenericIdentityFn<T> {
    (arg: T): T;
}

let myIdentity: GenericIdentityFn<number> = identity;

// 泛型类
class GenericNumber<T> {
    zeroValue: T;
    add: (x: T, y: T) => T;
}

let myGenericNumber = new GenericNumber<number>();
myGenericNumber.zeroValue = 0;
myGenericNumber.add = function(x, y) { return x + y; };
```

## 6. 高级类型

```typescript
// 联合类型
function padLeft(value: string, padding: string | number) {
    // ...
}

// 类型别名
type Name = string;
type NameResolver = () => string;
type NameOrResolver = Name | NameResolver;

// 字符串字面量类型
type Easing = "ease-in" | "ease-out" | "ease-in-out";

// 交叉类型
interface ErrorHandling {
    success: boolean;
    error?: { message: string };
}

interface ArtworksData {
    artworks: { title: string }[];
}

type ArtworksResponse = ArtworksData & ErrorHandling;
```

## 7. 力扣题目中常用的 TypeScript 技巧

```typescript
// 二维数组初始化
function create2DArray<T>(rows: number, cols: number, defaultValue: T): T[][] {
    return Array(rows).fill(0).map(() => Array(cols).fill(defaultValue));
}

let dp = create2DArray(3, 3, 0);

// 类型断言
function getLength(obj: string | string[]) {
    if ((obj as string[]).length) { // 类型断言
        return (obj as string[]).length;
    } else {
        return (obj as string).length;
    }
}

// 使用 Record 类型创建字典
type Dictionary = Record<string, number>;
let wordCount: Dictionary = {};
wordCount["apple"] = 5;

// 使用 Map 代替对象作为字典
let map = new Map<string, number>();
map.set("apple", 5);

// 使用 Set 存储唯一值
let uniqueNumbers = new Set<number>();
uniqueNumbers.add(1);
uniqueNumbers.add(2);
uniqueNumbers.add(1); // 不会重复添加
```

## 8. TypeScript 与 JavaScript 的主要区别

1. **静态类型检查**：TypeScript 在编译时进行类型检查，而 JavaScript 是动态类型的。

2. **类型注解**：TypeScript 允许为变量、函数参数和返回值添加类型注解。

3. **接口和类型**：TypeScript 提供了接口和高级类型系统，用于定义复杂数据结构。

4. **编译过程**：TypeScript 代码需要编译成 JavaScript 才能运行。

5. **IDE 支持**：TypeScript 提供更好的代码补全和错误提示。

6. **ECMAScript 特性**：TypeScript 支持最新的 ECMAScript 特性，并可以编译为兼容旧浏览器的 JavaScript。