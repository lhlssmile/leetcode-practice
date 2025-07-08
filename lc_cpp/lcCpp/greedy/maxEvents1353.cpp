//
// Created by 24276 on 2025/7/7.
//
#define V vector
#define pb push_back
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class max_events1353 {
public:
    int maxEvents(V<V<int>>& events) {
        // 按开始时间排序
        sort(events.begin(), events.end());

        // 优先队列存储结束时间（小根堆）
        priority_queue<int, vector<int>, greater<int>> pq;

        int day = 1;
        int i = 0;
        int result = 0;

        // 当还有会议或队列不为空时继续
        while (i < events.size() || !pq.empty()) {
            // 将当天开始的所有会议加入队列
            while (i < events.size() && events[i][0] <= day) {
                pq.push(events[i][1]); // 加入结束时间
                i++;
            }

            // 移除已经过期的会议（结束时间 < 当前天）
            while (!pq.empty() && pq.top() < day) {
                pq.pop();
            }

            // 如果有可参加的会议，选择最早结束的
            if (!pq.empty()) {
                pq.pop(); // 参加这个会议
                result++;
            }

            day++;
        }

        return result;
    }
};

int main() {
    max_events1353 ps;
    vector<vector<int>> events = {
        {1,2},{2,3},{3,4}
    };
    cout << "最大会议数: " << ps.maxEvents(events) << endl;

    // 测试用例2
    vector<vector<int>> events2 = {
        {1,2},{2,3},{3,4},{1,2}
    };
    cout << "测试用例2: " << ps.maxEvents(events2) << endl;

    // 测试用例3
    vector<vector<int>> events3 = {
        {1,4},{4,4},{2,2},{3,4},{1,1}
    };
    cout << "测试用例3: " << ps.maxEvents(events3) << endl;

    return 0;
}