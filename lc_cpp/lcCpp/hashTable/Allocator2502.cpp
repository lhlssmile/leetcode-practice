#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
class allocator2502 {
#define SIZE 1000
public:
    vector<int> a;      //memory array
    unordered_map<int,vector<int>> map; //record every mId分配的内存块
    allocator2502(int n) : a(n){};
    int allocate(int size, int mID) {
        int n = a.size();
        int start = 0;  // 起始下标

        // 查找第一个足够大的连续空闲内存块
        while (start <= n - size) {
            if (a[start] == 0) {
                bool isFree = true;
                for (int i = start; i < start + size; ++i) {
                    if (a[i] != 0) {
                        isFree = false;
                        start = i + 1;  // 跳过已分配的内存单元
                        break;
                    }
                }
                if (isFree) {
                    // 分配内存
                    for (int i = start; i < start + size; ++i) {
                        a[i] = mID;
                    }
                    map[mID].push_back(start);  // 记录分配的内存块
                    return start;
                }
            } else {
                start++;
            }
        }
        return -1;  // 没有足够大的连续空闲内存块
    }

    int freeMemory(int mID) {
        if (map.find(mID) == map.end()) {
            return 0;  // 没有分配过该 mID
        }

        int freed = 0;
        for (int start : map[mID]) {
            // 释放内存
            for (int i = start; i < a.size() && a[i] == mID; ++i) {
                a[i] = 0;  // 标记为空闲
                freed++;
            }
        }
        map.erase(mID);  // 删除 mID 的记录
        return freed;
    }
};

int main() {
    auto ps = new allocator2502(10);
    ps->allocate(1,1);
    ps->allocate(1,2);
    ps->allocate(1,3);
    ps->freeMemory(2);
    ps->allocate(3,4);
    ps->allocate(1,1);
    ps->allocate(1,1);
    ps->freeMemory(1);
    ps->allocate(10,2);
    ps->freeMemory(7);
    return 0;
}
