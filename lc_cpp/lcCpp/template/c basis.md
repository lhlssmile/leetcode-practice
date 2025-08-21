# C语言基础知识详解

## 目录
1. [基本数据类型](#基本数据类型)
2. [指针](#指针)
3. [内存管理](#内存管理)
4. [引用](#引用)
5. [结构体](#结构体)
6. [函数](#函数)
7. [预处理器](#预处理器)
8. [文件操作](#文件操作)

## 基本数据类型

### 整型

```c
// 整型数据类型
char c = 'A';           // 1字节，通常用于表示字符，但也是一种整型
short s = 123;          // 2字节
int i = 12345;          // 通常为4字节
long l = 123456789L;    // 在32位系统上为4字节，64位系统上通常为8字节
long long ll = 123456789012345LL;  // 8字节

// 无符号类型
unsigned char uc = 255;          // 0 到 255
unsigned short us = 65535;       // 0 到 65,535
unsigned int ui = 4294967295U;   // 0 到 4,294,967,295
unsigned long ul = 4294967295UL; // 范围取决于系统
```

### 浮点型

```c
// 浮点数据类型
float f = 3.14159F;        // 4字节，精度约为7位小数
double d = 3.141592653589793; // 8字节，精度约为15位小数
long double ld = 3.141592653589793238L; // 通常为16字节，但取决于编译器
```

### 类型修饰符

```c
// 类型修饰符
const int CONSTANT = 100;    // 常量，不可修改
volatile int v_int;          // 告诉编译器该变量可能会被外部修改
restrict int *r_ptr;         // C99特性，告诉编译器该指针是访问其指向对象的唯一方式
```

### 类型转换

```c
// 隐式类型转换
int i = 10;
double d = i;    // int 隐式转换为 double

// 显式类型转换（强制类型转换）
double pi = 3.14159;
int rounded = (int)pi;    // 强制将 double 转换为 int，结果为 3
```

## 指针

### 基本概念

指针是存储内存地址的变量。通过指针，我们可以间接访问和修改内存中的数据。

```c
// 声明和初始化指针
int num = 10;
int *ptr = &num;    // ptr 存储 num 的内存地址

// 通过指针访问和修改值
printf("num的值: %d\n", num);       // 输出: 10
printf("num的地址: %p\n", &num);    // 输出: num的内存地址
printf("ptr的值: %p\n", ptr);       // 输出: 与&num相同
printf("ptr指向的值: %d\n", *ptr);   // 输出: 10

*ptr = 20;    // 通过指针修改 num 的值
printf("修改后num的值: %d\n", num);  // 输出: 20
```

### 指针算术

```c
// 指针算术
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;    // p 指向数组的第一个元素

printf("%d\n", *p);        // 输出: 10
printf("%d\n", *(p+1));    // 输出: 20
printf("%d\n", *(p+2));    // 输出: 30

// 等价于使用数组索引
printf("%d\n", arr[0]);    // 输出: 10
printf("%d\n", arr[1]);    // 输出: 20
printf("%d\n", arr[2]);    // 输出: 30
```

### 指针与数组

```c
// 指针与数组
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;    // 数组名是指向第一个元素的指针

// 使用指针遍历数组
for (int i = 0; i < 5; i++) {
    printf("%d ", *(p + i));    // 输出: 10 20 30 40 50
}

// 另一种遍历方式
for (p = arr; p < arr + 5; p++) {
    printf("%d ", *p);    // 输出: 10 20 30 40 50
}
```

### 指针与字符串

```c
// 指针与字符串
char str[] = "Hello";
char *p_str = str;

// 使用指针遍历字符串
while (*p_str != '\0') {
    printf("%c", *p_str);
    p_str++;
}
// 输出: Hello
```

### 指针的指针（多级指针）

```c
// 指针的指针
int num = 10;
int *p = &num;      // 一级指针
int **pp = &p;      // 二级指针

printf("%d\n", num);     // 输出: 10
printf("%d\n", *p);      // 输出: 10
printf("%d\n", **pp);    // 输出: 10

**pp = 20;    // 通过二级指针修改 num 的值
printf("%d\n", num);     // 输出: 20
```

### 函数指针

```c
// 函数指针
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    // 声明函数指针
    int (*operation)(int, int);
    
    // 指向add函数
    operation = add;
    printf("%d\n", operation(5, 3));    // 输出: 8
    
    // 指向subtract函数
    operation = subtract;
    printf("%d\n", operation(5, 3));    // 输出: 2
    
    return 0;
}
```

### void指针

```c
// void指针 - 通用指针类型
void *ptr;

int i = 10;
double d = 3.14;
char c = 'A';

// void指针可以指向任何类型的数据
ptr = &i;
printf("%d\n", *(int*)ptr);    // 需要强制类型转换，输出: 10

ptr = &d;
printf("%f\n", *(double*)ptr);    // 输出: 3.140000

ptr = &c;
printf("%c\n", *(char*)ptr);    // 输出: A
```

### NULL指针

```c
// NULL指针
int *ptr = NULL;    // 初始化为NULL指针

// 检查指针是否为NULL
if (ptr == NULL) {
    printf("ptr是NULL指针\n");
}

// 避免解引用NULL指针
if (ptr != NULL) {
    printf("%d\n", *ptr);    // 只有在ptr不为NULL时才解引用
}
```

## 内存管理

### 内存布局

C程序的内存布局通常包括以下几个部分：

1. **代码段（Text Segment）**：存储程序的机器代码。
2. **数据段（Data Segment）**：存储已初始化的全局变量和静态变量。
3. **BSS段（BSS Segment）**：存储未初始化的全局变量和静态变量。
4. **堆（Heap）**：动态分配的内存区域。
5. **栈（Stack）**：存储局部变量、函数参数和返回地址。

### 动态内存分配

```c
#include <stdlib.h>

// 动态内存分配
int *ptr;

// 分配内存
ptr = (int*)malloc(5 * sizeof(int));    // 分配5个int大小的内存

// 检查内存分配是否成功
if (ptr == NULL) {
    printf("内存分配失败\n");
    exit(1);
}

// 使用分配的内存
for (int i = 0; i < 5; i++) {
    ptr[i] = i * 10;
}

// 释放内存
free(ptr);
ptr = NULL;    // 避免悬挂指针
```

### calloc和realloc

```c
// calloc - 分配并初始化内存为0
int *ptr1 = (int*)calloc(5, sizeof(int));    // 分配5个int大小的内存，并初始化为0

// realloc - 调整已分配内存的大小
ptr1 = (int*)realloc(ptr1, 10 * sizeof(int));    // 将内存调整为10个int大小

// 释放内存
free(ptr1);
ptr1 = NULL;
```

### 实现动态数组（类似C++的vector）

在C语言中，没有像C++中vector那样的内置动态数组，但我们可以使用动态内存分配来实现类似的功能：

```c
#include <stdio.h>
#include <stdlib.h>

// 定义动态数组结构
typedef struct {
    int* array;     // 指向数据的指针
    size_t size;    // 当前元素数量
    size_t capacity; // 当前分配的容量
} DynamicArray;

// 初始化动态数组
void initArray(DynamicArray* arr, size_t initialCapacity) {
    arr->array = (int*)malloc(initialCapacity * sizeof(int));
    if (arr->array == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = initialCapacity;
}

// 添加元素到动态数组末尾
void pushBack(DynamicArray* arr, int element) {
    // 检查是否需要扩容
    if (arr->size == arr->capacity) {
        // 通常扩容为当前容量的2倍
        size_t newCapacity = arr->capacity * 2;
        int* newArray = (int*)realloc(arr->array, newCapacity * sizeof(int));
        if (newArray == NULL) {
            printf("内存重新分配失败\n");
            exit(1);
        }
        arr->array = newArray;
        arr->capacity = newCapacity;
    }
    
    // 添加新元素
    arr->array[arr->size] = element;
    arr->size++;
}

// 获取指定索引的元素
int getElement(DynamicArray* arr, size_t index) {
    if (index >= arr->size) {
        printf("索引越界\n");
        exit(1);
    }
    return arr->array[index];
}

// 设置指定索引的元素值
void setElement(DynamicArray* arr, size_t index, int value) {
    if (index >= arr->size) {
        printf("索引越界\n");
        exit(1);
    }
    arr->array[index] = value;
}

// 从动态数组末尾移除元素
int popBack(DynamicArray* arr) {
    if (arr->size == 0) {
        printf("数组为空，无法移除元素\n");
        exit(1);
    }
    arr->size--;
    return arr->array[arr->size];
}

// 释放动态数组内存
void freeArray(DynamicArray* arr) {
    free(arr->array);
    arr->array = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

// 使用示例
int main() {
    DynamicArray myArray;
    initArray(&myArray, 4);  // 初始容量为4
    
    // 添加元素
    for (int i = 0; i < 10; i++) {
        pushBack(&myArray, i * 10);
        printf("添加元素: %d, 当前大小: %zu, 当前容量: %zu\n", 
               i * 10, myArray.size, myArray.capacity);
    }
    
    // 访问元素
    printf("\n数组内容: ");
    for (size_t i = 0; i < myArray.size; i++) {
        printf("%d ", getElement(&myArray, i));
    }
    printf("\n");
    
    // 修改元素
    setElement(&myArray, 5, 999);
    printf("修改后索引5的值: %d\n", getElement(&myArray, 5));
    
    // 移除元素
    int lastElement = popBack(&myArray);
    printf("移除的最后一个元素: %d, 移除后大小: %zu\n", lastElement, myArray.size);
    
    // 释放内存
    freeArray(&myArray);
    
    return 0;
}
```

这个实现提供了类似C++中vector的基本功能：

1. **自动扩容**：当空间不足时，自动分配更多内存（通常是当前容量的2倍）
2. **添加元素**：pushBack函数类似于vector的push_back
3. **访问元素**：getElement和setElement函数类似于vector的[]操作符
4. **移除元素**：popBack函数类似于vector的pop_back
5. **内存管理**：自动处理内存分配和释放

与C++的vector相比，这个实现有一些限制：

1. 只能存储一种类型的数据（这里是int）
2. 没有迭代器
3. 没有提供像insert、erase这样的高级操作
4. 需要手动调用freeArray释放内存

如果需要更通用的实现，可以使用void指针和函数指针来处理不同类型的数据，或者使用宏来生成针对不同类型的代码。

### 内存泄漏

内存泄漏是指程序分配了内存但未释放，导致该内存无法被重新使用。

```c
// 内存泄漏示例
void memory_leak() {
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 10;
    // 函数结束时没有调用free(ptr)，导致内存泄漏
}

// 正确的做法
void no_memory_leak() {
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 10;
    // 使用完毕后释放内存
    free(ptr);
    ptr = NULL;
}
```

## 引用（C++特性）

注意：引用是C++的特性，不是C语言的一部分。但由于用户提到了C++，这里简要介绍引用。

```cpp
// C++中的引用
#include <iostream>
using namespace std;

int main() {
    int num = 10;
    int &ref = num;    // ref是num的引用
    
    cout << "num: " << num << endl;    // 输出: 10
    cout << "ref: " << ref << endl;    // 输出: 10
    
    ref = 20;    // 通过引用修改num的值
    cout << "num: " << num << endl;    // 输出: 20
    
    num = 30;    // 直接修改num的值
    cout << "ref: " << ref << endl;    // 输出: 30
    
    return 0;
}
```

### 引用与指针的区别

1. 引用必须在声明时初始化，指针可以在任何时候初始化。
2. 引用一旦初始化后不能改变引用的对象，指针可以改变指向的对象。
3. 引用不能为NULL，指针可以为NULL。
4. 引用不占用额外的内存，指针是一个实际的变量，需要存储地址。

```cpp
// 引用作为函数参数
void swap_by_reference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// 指针作为函数参数
void swap_by_pointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    
    swap_by_reference(x, y);    // 使用引用交换
    cout << "x: " << x << ", y: " << y << endl;    // 输出: x: 10, y: 5
    
    swap_by_pointer(&x, &y);    // 使用指针交换
    cout << "x: " << x << ", y: " << y << endl;    // 输出: x: 5, y: 10
    
    return 0;
}
```

## 结构体

### 基本用法

```c
// 定义结构体
struct Person {
    char name[50];
    int age;
    float height;
};

int main() {
    // 声明结构体变量
    struct Person person1;
    
    // 初始化结构体成员
    strcpy(person1.name, "张三");
    person1.age = 25;
    person1.height = 175.5;
    
    // 访问结构体成员
    printf("姓名: %s\n", person1.name);
    printf("年龄: %d\n", person1.age);
    printf("身高: %.1f cm\n", person1.height);
    
    return 0;
}
```

### 结构体初始化

```c
// 结构体初始化
struct Person person2 = {"李四", 30, 180.0};

// C99支持指定初始化器
struct Person person3 = {
    .name = "王五",
    .age = 35,
    .height = 170.0
};
```

### 结构体数组

```c
// 结构体数组
struct Person people[3] = {
    {"张三", 25, 175.5},
    {"李四", 30, 180.0},
    {"王五", 35, 170.0}
};

// 访问结构体数组
for (int i = 0; i < 3; i++) {
    printf("姓名: %s, 年龄: %d, 身高: %.1f cm\n",
           people[i].name, people[i].age, people[i].height);
}
```

### 结构体指针

```c
// 结构体指针
struct Person *p_person = &person1;

// 通过指针访问结构体成员
printf("姓名: %s\n", p_person->name);        // 使用箭头操作符
printf("年龄: %d\n", (*p_person).age);      // 使用点操作符（需要解引用）
printf("身高: %.1f cm\n", p_person->height);
```

### 嵌套结构体

```c
// 嵌套结构体
struct Address {
    char street[100];
    char city[50];
    char country[50];
};

struct Employee {
    char name[50];
    int id;
    struct Address address;    // 嵌套结构体
};

// 使用嵌套结构体
struct Employee emp = {
    "张三",
    1001,
    {"中关村大街", "北京", "中国"}
};

// 访问嵌套结构体成员
printf("员工姓名: %s\n", emp.name);
printf("员工ID: %d\n", emp.id);
printf("地址: %s, %s, %s\n",
       emp.address.street, emp.address.city, emp.address.country);
```

### 结构体与函数

```c
// 结构体作为函数参数（传值）
void print_person(struct Person p) {
    printf("姓名: %s, 年龄: %d, 身高: %.1f cm\n",
           p.name, p.age, p.height);
}

// 结构体指针作为函数参数（传引用）
void update_age(struct Person *p, int new_age) {
    p->age = new_age;
}

// 返回结构体的函数
struct Person create_person(const char *name, int age, float height) {
    struct Person p;
    strcpy(p.name, name);
    p.age = age;
    p.height = height;
    return p;
}
```

### 结构体中的位域

```c
// 位域 - 节省内存空间
struct Flags {
    unsigned int is_active : 1;    // 只使用1位
    unsigned int is_male : 1;       // 只使用1位
    unsigned int age : 7;           // 使用7位，可表示0-127
};

// 使用位域
struct Flags user = {1, 1, 25};    // 活跃，男性，25岁

printf("活跃: %d\n", user.is_active);
printf("性别: %s\n", user.is_male ? "男" : "女");
printf("年龄: %d\n", user.age);
```

### 联合体（Union）

```c
// 联合体 - 共享内存空间
union Data {
    int i;
    float f;
    char str[20];
};

// 使用联合体
union Data data;

data.i = 10;
printf("data.i: %d\n", data.i);

data.f = 3.14;
printf("data.f: %f\n", data.f);    // 此时data.i的值已被覆盖

strcpy(data.str, "Hello");
printf("data.str: %s\n", data.str);    // 此时data.i和data.f的值已被覆盖
```

## 函数

### 函数声明与定义

```c
// 函数声明（原型）
int add(int a, int b);    // 声明函数但不定义

// 函数定义
int add(int a, int b) {
    return a + b;
}

// 使用函数
int result = add(5, 3);    // result = 8
```

### 函数参数

```c
// 值传递 - 函数内的修改不影响原始值
void increment_by_value(int a) {
    a++;    // 只修改局部副本
}

// 指针传递 - 函数内的修改会影响原始值
void increment_by_pointer(int *a) {
    (*a)++;    // 修改指针指向的值
}

int main() {
    int x = 10;
    
    increment_by_value(x);
    printf("x after increment_by_value: %d\n", x);    // 输出: 10（未改变）
    
    increment_by_pointer(&x);
    printf("x after increment_by_pointer: %d\n", x);    // 输出: 11（已改变）
    
    return 0;
}
```

### 数组作为函数参数

```c
// 数组作为函数参数
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 等价写法
void print_array_ptr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    print_array(numbers, size);
    print_array_ptr(numbers, size);
    
    return 0;
}
```

### 可变参数函数

```c
#include <stdarg.h>

// 可变参数函数
int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    return total;
}

int main() {
    printf("Sum: %d\n", sum(3, 10, 20, 30));    // 输出: Sum: 60
    printf("Sum: %d\n", sum(5, 1, 2, 3, 4, 5));    // 输出: Sum: 15
    
    return 0;
}
```

### 递归函数

```c
// 递归函数 - 计算阶乘
int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    printf("5! = %d\n", factorial(5));    // 输出: 5! = 120
    
    return 0;
}
```

### 内联函数

```c
// 内联函数 - 减少函数调用开销
inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int result = max(10, 20);    // 编译器可能会将函数调用替换为直接代码
    printf("Max: %d\n", result);    // 输出: Max: 20
    
    return 0;
}
```

### 静态函数

```c
// 静态函数 - 只在当前文件可见
static int private_function() {
    return 42;
}

// 非静态函数 - 可以在其他文件中使用（需要声明）
int public_function() {
    return private_function() * 2;
}
```

## 预处理器

### 宏定义

```c
// 简单的宏定义
#define PI 3.14159
#define MAX_SIZE 100

// 带参数的宏
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 使用宏
double area = PI * SQUARE(radius);
int max_value = MAX(x, y);
```

### 条件编译

```c
// 条件编译
#define DEBUG 1

#if DEBUG
    printf("Debug模式: 变量x = %d\n", x);
#else
    printf("Release模式\n");
#endif

// 检查是否定义了某个宏
#ifdef DEBUG
    // DEBUG已定义时执行的代码
#endif

#ifndef DEBUG
    // DEBUG未定义时执行的代码
#endif
```

### 文件包含

```c
// 包含标准库头文件
#include <stdio.h>
#include <stdlib.h>

// 包含自定义头文件
#include "myheader.h"
```

### 预定义宏

```c
// 预定义宏
printf("文件: %s\n", __FILE__);
printf("行号: %d\n", __LINE__);
printf("编译日期: %s\n", __DATE__);
printf("编译时间: %s\n", __TIME__);
printf("ANSI C: %d\n", __STDC__);
```

## 文件操作

### 基本文件操作

```c
#include <stdio.h>

// 打开文件
FILE *file = fopen("example.txt", "r");    // 只读模式

// 检查文件是否成功打开
if (file == NULL) {
    perror("无法打开文件");
    return 1;
}

// 关闭文件
fclose(file);
```

### 文件读写

```c
// 写入文件
FILE *file = fopen("output.txt", "w");    // 写入模式（会覆盖已有内容）

if (file != NULL) {
    fprintf(file, "Hello, World!\n");    // 格式化写入
    fputs("这是第二行\n", file);         // 写入字符串
    fputc('A', file);                    // 写入单个字符
    
    fclose(file);
}

// 读取文件
file = fopen("output.txt", "r");    // 只读模式

if (file != NULL) {
    char buffer[100];
    
    // 按行读取
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    // 或者按字符读取
    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    
    fclose(file);
}
```

### 二进制文件操作

```c
// 二进制文件写入
struct Person person = {"张三", 25, 175.5};

FILE *file = fopen("person.bin", "wb");    // 二进制写入模式

if (file != NULL) {
    fwrite(&person, sizeof(struct Person), 1, file);
    fclose(file);
}

// 二进制文件读取
struct Person read_person;

file = fopen("person.bin", "rb");    // 二进制读取模式

if (file != NULL) {
    fread(&read_person, sizeof(struct Person), 1, file);
    printf("姓名: %s, 年龄: %d, 身高: %.1f cm\n",
           read_person.name, read_person.age, read_person.height);
    fclose(file);
}
```

### 文件定位

```c
// 文件定位
FILE *file = fopen("example.txt", "r+");    // 读写模式

if (file != NULL) {
    // 移动到文件开头后的10个字节处
    fseek(file, 10, SEEK_SET);
    
    // 获取当前位置
    long position = ftell(file);
    printf("当前位置: %ld\n", position);
    
    // 移动到文件末尾
    fseek(file, 0, SEEK_END);
    
    // 获取文件大小
    long size = ftell(file);
    printf("文件大小: %ld 字节\n", size);
    
    // 回到文件开头
    rewind(file);
    
    fclose(file);
}
```

---

这个文档涵盖了C语言的基础知识，包括数据类型、指针、内存管理、结构体、函数等内容。由于用户提到了C++，我也简要介绍了C++中的引用概念。希望这个文档对学习和复习C语言基础知识有所帮助！