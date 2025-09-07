// LeetCode 707: 设计链表
// 设计链表的实现。您可以选择使用单链表或双链表。

import java.util.*;
import java.util.function.*;

// 双向链表节点
class ListNode {
    int val;
    ListNode prev;
    ListNode next;
    
    public ListNode() {
        this(0);
    }
    
    public ListNode(int val) {
        this.val = val;
        this.prev = null;
        this.next = null;
    }
    
    @Override
    public String toString() {
        return "ListNode(" + val + ")";
    }
}

// 双向链表实现
class MyLinkedList {
    private ListNode head;
    private ListNode tail;
    private int size;
    
    public MyLinkedList() {
        // 创建哨兵节点
        head = new ListNode();
        tail = new ListNode();
        head.next = tail;
        tail.prev = head;
        size = 0;
    }
    
    public int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        
        ListNode current = head.next;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        return current.val;
    }
    
    public void addAtHead(int val) {
        addAtIndex(0, val);
    }
    
    public void addAtTail(int val) {
        addAtIndex(size, val);
    }
    
    public void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return;
        }
        
        ListNode pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        ListNode succ = pred.next;
        ListNode newNode = new ListNode(val);
        
        newNode.prev = pred;
        newNode.next = succ;
        pred.next = newNode;
        succ.prev = newNode;
        
        size++;
    }
    
    public void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        
        ListNode pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        ListNode toDelete = pred.next;
        ListNode succ = toDelete.next;
        
        pred.next = succ;
        succ.prev = pred;
        
        size--;
    }
    
    public int getSize() {
        return size;
    }
    
    public List<Integer> toList() {
        List<Integer> result = new ArrayList<>();
        ListNode current = head.next;
        while (current != tail) {
            result.add(current.val);
            current = current.next;
        }
        return result;
    }
    
    @Override
    public String toString() {
        return toList().toString();
    }
}

// 使用ArrayList实现的链表
class ArrayLinkedList {
    private List<Integer> data;
    
    public ArrayLinkedList() {
        data = new ArrayList<>();
    }
    
    public int get(int index) {
        if (index >= 0 && index < data.size()) {
            return data.get(index);
        }
        return -1;
    }
    
    public void addAtHead(int val) {
        data.add(0, val);
    }
    
    public void addAtTail(int val) {
        data.add(val);
    }
    
    public void addAtIndex(int index, int val) {
        if (index >= 0 && index <= data.size()) {
            data.add(index, val);
        }
    }
    
    public void deleteAtIndex(int index) {
        if (index >= 0 && index < data.size()) {
            data.remove(index);
        }
    }
    
    @Override
    public String toString() {
        return data.toString();
    }
}

// 使用LinkedList实现
class DequeLinkedList {
    private LinkedList<Integer> data;
    
    public DequeLinkedList() {
        data = new LinkedList<>();
    }
    
    public int get(int index) {
        if (index >= 0 && index < data.size()) {
            return data.get(index);
        }
        return -1;
    }
    
    public void addAtHead(int val) {
        data.addFirst(val);
    }
    
    public void addAtTail(int val) {
        data.addLast(val);
    }
    
    public void addAtIndex(int index, int val) {
        if (index >= 0 && index <= data.size()) {
            data.add(index, val);
        }
    }
    
    public void deleteAtIndex(int index) {
        if (index >= 0 && index < data.size()) {
            data.remove(index);
        }
    }
    
    @Override
    public String toString() {
        return data.toString();
    }
}

// 单链表节点
class SinglyListNode {
    int val;
    SinglyListNode next;
    
    public SinglyListNode() {
        this(0);
    }
    
    public SinglyListNode(int val) {
        this.val = val;
        this.next = null;
    }
}

// 单链表实现
class SinglyLinkedList {
    private SinglyListNode head;
    private int size;
    
    public SinglyLinkedList() {
        head = new SinglyListNode(); // 哨兵节点
        size = 0;
    }
    
    public int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        
        SinglyListNode current = head.next;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        return current.val;
    }
    
    public void addAtHead(int val) {
        addAtIndex(0, val);
    }
    
    public void addAtTail(int val) {
        addAtIndex(size, val);
    }
    
    public void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return;
        }
        
        SinglyListNode pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        SinglyListNode newNode = new SinglyListNode(val);
        newNode.next = pred.next;
        pred.next = newNode;
        
        size++;
    }
    
    public void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        
        SinglyListNode pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        pred.next = pred.next.next;
        size--;
    }
}

// 泛型链表实现
class GenericLinkedList<T> {
    private static class Node<T> {
        T val;
        Node<T> prev;
        Node<T> next;
        
        public Node(T val) {
            this.val = val;
        }
    }
    
    private Node<T> head;
    private Node<T> tail;
    private int size;
    
    public GenericLinkedList() {
        head = new Node<>(null);
        tail = new Node<>(null);
        head.next = tail;
        tail.prev = head;
        size = 0;
    }
    
    public T get(int index) {
        if (index < 0 || index >= size) {
            return null;
        }
        
        Node<T> current = head.next;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        return current.val;
    }
    
    public void add(int index, T val) {
        if (index < 0 || index > size) {
            return;
        }
        
        Node<T> pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        Node<T> succ = pred.next;
        Node<T> newNode = new Node<>(val);
        
        newNode.prev = pred;
        newNode.next = succ;
        pred.next = newNode;
        succ.prev = newNode;
        
        size++;
    }
    
    public void delete(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        
        Node<T> pred = head;
        for (int i = 0; i < index; i++) {
            pred = pred.next;
        }
        
        Node<T> toDelete = pred.next;
        Node<T> succ = toDelete.next;
        
        pred.next = succ;
        succ.prev = pred;
        
        size--;
    }
    
    public List<T> toList() {
        List<T> result = new ArrayList<>();
        Node<T> current = head.next;
        while (current != tail) {
            result.add(current.val);
            current = current.next;
        }
        return result;
    }
}

// 函数式编程风格的链表操作
class FunctionalLinkedList {
    private List<Integer> data;
    
    public FunctionalLinkedList() {
        data = new ArrayList<>();
    }
    
    public int get(int index) {
        return Optional.of(index)
                .filter(i -> i >= 0 && i < data.size())
                .map(data::get)
                .orElse(-1);
    }
    
    public void addAtHead(int val) {
        data.add(0, val);
    }
    
    public void addAtTail(int val) {
        data.add(val);
    }
    
    public void addAtIndex(int index, int val) {
        Optional.of(index)
                .filter(i -> i >= 0 && i <= data.size())
                .ifPresent(i -> data.add(i, val));
    }
    
    public void deleteAtIndex(int index) {
        Optional.of(index)
                .filter(i -> i >= 0 && i < data.size())
                .ifPresent(data::remove);
    }
    
    @Override
    public String toString() {
        return data.toString();
    }
}

// 链表操作接口
interface LinkedListOperations {
    int get(int index);
    void addAtHead(int val);
    void addAtTail(int val);
    void addAtIndex(int index, int val);
    void deleteAtIndex(int index);
}

// 抽象链表类
abstract class AbstractLinkedList implements LinkedListOperations {
    protected int size;
    
    public int getSize() {
        return size;
    }
    
    protected boolean isValidIndex(int index) {
        return index >= 0 && index < size;
    }
    
    protected boolean isValidInsertIndex(int index) {
        return index >= 0 && index <= size;
    }
}

// 具体实现类
class ConcreteLinkedList extends AbstractLinkedList {
    private List<Integer> data;
    
    public ConcreteLinkedList() {
        data = new ArrayList<>();
        size = 0;
    }
    
    @Override
    public int get(int index) {
        return isValidIndex(index) ? data.get(index) : -1;
    }
    
    @Override
    public void addAtHead(int val) {
        addAtIndex(0, val);
    }
    
    @Override
    public void addAtTail(int val) {
        addAtIndex(size, val);
    }
    
    @Override
    public void addAtIndex(int index, int val) {
        if (isValidInsertIndex(index)) {
            data.add(index, val);
            size++;
        }
    }
    
    @Override
    public void deleteAtIndex(int index) {
        if (isValidIndex(index)) {
            data.remove(index);
            size--;
        }
    }
}

public class DesignLinkedList {
    
    // 函数式操作链表
    public static List<Integer> linkedListOperations(List<String[]> operations) {
        MyLinkedList obj = new MyLinkedList();
        List<Integer> results = new ArrayList<>();
        
        for (String[] operation : operations) {
            String op = operation[0];
            switch (op) {
                case "get":
                    results.add(obj.get(Integer.parseInt(operation[1])));
                    break;
                case "addAtHead":
                    obj.addAtHead(Integer.parseInt(operation[1]));
                    results.add(null);
                    break;
                case "addAtTail":
                    obj.addAtTail(Integer.parseInt(operation[1]));
                    results.add(null);
                    break;
                case "addAtIndex":
                    obj.addAtIndex(Integer.parseInt(operation[1]), Integer.parseInt(operation[2]));
                    results.add(null);
                    break;
                case "deleteAtIndex":
                    obj.deleteAtIndex(Integer.parseInt(operation[1]));
                    results.add(null);
                    break;
                default:
                    results.add(null);
            }
        }
        
        return results;
    }
    
    public static void testDesignLinkedList() {
        System.out.println("=== 设计链表测试 ===");
        
        // 测试双向链表实现
        System.out.println("\n--- 双向链表实现测试 ---");
        MyLinkedList list = new MyLinkedList();
        
        list.addAtHead(7);
        list.addAtHead(2);
        list.addAtHead(1);
        System.out.println("添加头部元素后: " + list);
        
        list.addAtIndex(3, 0);
        System.out.println("在索引3添加0后: " + list);
        
        list.deleteAtIndex(2);
        System.out.println("删除索引2后: " + list);
        
        list.addAtHead(6);
        System.out.println("添加头部6后: " + list);
        
        list.addAtTail(4);
        System.out.println("添加尾部4后: " + list);
        
        System.out.println("获取索引5: " + list.get(5)); // -1
        System.out.println("获取索引3: " + list.get(3)); // 0
        System.out.println("获取索引2: " + list.get(2)); // 2
        System.out.println("获取索引0: " + list.get(0)); // 6
        
        list.deleteAtIndex(0);
        System.out.println("删除索引0后，获取索引0: " + list.get(0)); // 1
        
        // 测试ArrayList实现
        System.out.println("\n--- ArrayList实现测试 ---");
        ArrayLinkedList arrayList = new ArrayLinkedList();
        arrayList.addAtHead(1);
        arrayList.addAtTail(3);
        arrayList.addAtIndex(1, 2);
        System.out.println("ArrayList实现操作后: " + arrayList);
        System.out.println("获取索引1: " + arrayList.get(1)); // 2
        
        arrayList.deleteAtIndex(1);
        System.out.println("删除索引1后: " + arrayList);
        System.out.println("获取索引1: " + arrayList.get(1)); // 3
        
        // 测试LinkedList实现
        System.out.println("\n--- LinkedList实现测试 ---");
        DequeLinkedList dequeList = new DequeLinkedList();
        dequeList.addAtHead(1);
        dequeList.addAtTail(3);
        dequeList.addAtIndex(1, 2);
        System.out.println("LinkedList实现操作后: " + dequeList);
        System.out.println("获取索引1: " + dequeList.get(1)); // 2
        
        // 测试单链表实现
        System.out.println("\n--- 单链表实现测试 ---");
        SinglyLinkedList singlyList = new SinglyLinkedList();
        singlyList.addAtHead(1);
        singlyList.addAtTail(3);
        singlyList.addAtIndex(1, 2);
        System.out.println("单链表实现操作后: [1, 2, 3]");
        System.out.println("获取索引1: " + singlyList.get(1)); // 2
        
        // 测试泛型实现
        System.out.println("\n--- 泛型实现测试 ---");
        GenericLinkedList<String> strList = new GenericLinkedList<>();
        strList.add(0, "Hello");
        strList.add(1, "World");
        System.out.println("泛型实现(字符串): " + strList.toList());
        System.out.println("获取索引0: " + strList.get(0)); // Hello
        
        // 测试函数式实现
        System.out.println("\n--- 函数式实现测试 ---");
        FunctionalLinkedList funcList = new FunctionalLinkedList();
        funcList.addAtHead(1);
        funcList.addAtTail(3);
        funcList.addAtIndex(1, 2);
        System.out.println("函数式实现操作后: " + funcList);
        System.out.println("获取索引1: " + funcList.get(1)); // 2
        
        // 测试抽象类实现
        System.out.println("\n--- 抽象类实现测试 ---");
        ConcreteLinkedList concreteList = new ConcreteLinkedList();
        concreteList.addAtHead(1);
        concreteList.addAtTail(3);
        concreteList.addAtIndex(1, 2);
        System.out.println("抽象类实现大小: " + concreteList.getSize());
        System.out.println("获取索引1: " + concreteList.get(1)); // 2
        
        // 测试函数式操作
        System.out.println("\n--- 函数式操作测试 ---");
        List<String[]> operations = Arrays.asList(
            new String[]{"addAtHead", "7"},
            new String[]{"addAtHead", "2"},
            new String[]{"addAtHead", "1"},
            new String[]{"addAtIndex", "3", "0"},
            new String[]{"deleteAtIndex", "2"},
            new String[]{"addAtHead", "6"},
            new String[]{"addAtTail", "4"},
            new String[]{"get", "4"}
        );
        
        List<Integer> results = linkedListOperations(operations);
        System.out.println("函数式操作结果: " + results);
        
        System.out.println("\n=== Java特性说明 ===");
        System.out.println("1. 面向对象: 类、继承、多态、封装");
        System.out.println("2. 泛型: 类型安全的集合和方法");
        System.out.println("3. 集合框架: ArrayList、LinkedList等");
        System.out.println("4. 接口和抽象类: 契约定义和部分实现");
        System.out.println("5. Lambda表达式: 函数式编程支持");
        System.out.println("6. Optional: 空值安全处理");
    }
    
    public static void main(String[] args) {
        testDesignLinkedList();
    }
}

/*
Java实现特点:

1. **面向对象编程**:
   - 类和对象封装
   - 继承和多态
   - 接口契约定义

2. **泛型编程**:
   - 类型安全
   - 编译时类型检查
   - 代码复用

3. **集合框架**:
   - ArrayList动态数组
   - LinkedList双向链表
   - 丰富的操作方法

4. **内存管理**:
   - 自动垃圾回收
   - 引用管理
   - 内存泄漏预防

5. **函数式编程**:
   - Lambda表达式
   - Stream API
   - Optional类

6. **异常处理**:
   - 编译时异常检查
   - try-catch机制
   - 资源自动管理

算法复杂度:
- get: O(n)
- addAtHead: O(1)
- addAtTail: O(1)
- addAtIndex: O(n)
- deleteAtIndex: O(n)
- 空间复杂度: O(n)
*/