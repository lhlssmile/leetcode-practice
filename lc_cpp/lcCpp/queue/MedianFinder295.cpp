//
// Created by 24276 on 2025/7/18.
//
#define V vector
#define pb push_back
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

class MedianFinder {
public:
    // 方法1：双堆法（推荐）- O(log n) 插入，O(1) 查询
    priority_queue<int> maxHeap; // 存储较小的一半，大根堆
    priority_queue<int, vector<int>, greater<int>> minHeap; // 存储较大的一半，小根堆
    
    MedianFinder() {
        // 构造函数，无需初始化
    }
    
    void addNum(int num) {
        // 双堆平衡策略：
        // 1. maxHeap存储较小的一半（大根堆，堆顶是较小一半的最大值）
        // 2. minHeap存储较大的一半（小根堆，堆顶是较大一半的最小值）
        // 3. 保持 maxHeap.size() >= minHeap.size()，且差值不超过1
        
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // 平衡两个堆的大小
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};

// 方法2：简单排序法（适合面试时快速实现）
class MedianFinderSimple {
public:
    vector<int> arr;
    
    MedianFinderSimple() {}
    
    void addNum(int num) {
        // 插入排序，保持数组有序
        auto it = lower_bound(arr.begin(), arr.end(), num);
        arr.insert(it, num);
    }
    
    double findMedian() {
        int n = arr.size();
        if (n % 2 == 1) {
            return arr[n / 2];
        } else {
            return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
        }
    }
};

// 方法3：暴力排序法（最简单但效率低）
class MedianFinderBruteForce {
public:
    vector<int> arr;
    
    MedianFinderBruteForce() {}
    
    void addNum(int num) {
        arr.push_back(num);
    }
    
    double findMedian() {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        if (n % 2 == 1) {
            return arr[n / 2];
        } else {
            return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
        }
    }
};

// 测试函数
void testMedianFinder() {
    cout << "=== 测试双堆法 ===" << endl;
    MedianFinder mf;
    
    mf.addNum(1);
    cout << "添加1后，中位数: " << mf.findMedian() << endl; // 1.0
    
    mf.addNum(2);
    cout << "添加2后，中位数: " << mf.findMedian() << endl; // 1.5
    
    mf.addNum(3);
    cout << "添加3后，中位数: " << mf.findMedian() << endl; // 2.0
    
    mf.addNum(4);
    cout << "添加4后，中位数: " << mf.findMedian() << endl; // 2.5
    
    mf.addNum(5);
    cout << "添加5后，中位数: " << mf.findMedian() << endl; // 3.0
    
    cout << "\n=== 测试简单排序法 ===" << endl;
    MedianFinderSimple mfs;
    
    mfs.addNum(1);
    cout << "添加1后，中位数: " << mfs.findMedian() << endl;
    
    mfs.addNum(2);
    cout << "添加2后，中位数: " << mfs.findMedian() << endl;
    
    mfs.addNum(3);
    cout << "添加3后，中位数: " << mfs.findMedian() << endl;
}

int main() {
    testMedianFinder();
    
    cout << "\n=== 算法分析 ===" << endl;
    cout << "方法1：双堆法（推荐）" << endl;
    cout << "- addNum: O(log n)" << endl;
    cout << "- findMedian: O(1)" << endl;
    cout << "- 空间复杂度: O(n)" << endl;
    cout << "- 优点: 插入和查询都很高效" << endl;
    
    cout << "\n方法2：插入排序法" << endl;
    cout << "- addNum: O(n)" << endl;
    cout << "- findMedian: O(1)" << endl;
    cout << "- 空间复杂度: O(n)" << endl;
    cout << "- 优点: 实现简单，查询快" << endl;
    
    cout << "\n方法3：暴力排序法" << endl;
    cout << "- addNum: O(1)" << endl;
    cout << "- findMedian: O(n log n)" << endl;
    cout << "- 空间复杂度: O(n)" << endl;
    cout << "- 优点: 最简单的实现" << endl;
    
    cout << "\n核心思想：" << endl;
    cout << "双堆法利用大根堆存储较小一半，小根堆存储较大一半" << endl;
    cout << "通过维护堆的平衡，可以在O(1)时间内获取中位数" << endl;
    
    return 0;
}

/*
题目分析：数据流中位数

核心挑战：
1. 动态维护有序序列
2. 快速插入新元素
3. 快速查询中位数

三种解法对比：

方法1：双堆法（最优）
- 核心思想：用两个堆分别存储较小和较大的一半
- maxHeap（大根堆）：存储较小的一半，堆顶是较小一半的最大值
- minHeap（小根堆）：存储较大的一半，堆顶是较大一半的最小值
- 平衡策略：保持maxHeap.size() >= minHeap.size()，且差值不超过1
- 中位数获取：
  * 奇数个元素：maxHeap.top()
  * 偶数个元素：(maxHeap.top() + minHeap.top()) / 2.0

方法2：插入排序法
- 使用lower_bound找到插入位置
- 保持数组始终有序
- 查询中位数直接访问中间元素

方法3：暴力排序法
- 每次查询时重新排序
- 实现最简单但效率最低

关键洞察：
1. 双堆法的精髓在于分治思想
2. 通过堆的性质快速获取极值
3. 平衡策略确保中位数总是在堆顶附近

面试建议：
- 首选双堆法，展示对数据结构的深度理解
- 可以先提出简单解法，再优化到双堆法
- 注意边界情况和堆平衡的处理
*/
