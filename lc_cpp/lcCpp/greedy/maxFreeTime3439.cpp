//
// Created by 24276 on 2025/7/10.
//

#define V vector
#define pb push_back
#include <iostream>
#include <vector>
using namespace std;
class max_free_time3439 {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        // 滑动窗口 + 贪心  n个会议有n+1个空闲时间 ps: 左右
        int n = static_cast<int>(startTime.size());
        vector<int> free_t(n + 1);
        free_t[0] = startTime[0];   //存储两个会议之间的空闲间隔
        for(int i = 1;i < n;i++) {
            free_t[i] = startTime[i] - endTime[i - 1];
        }
        free_t[n] = eventTime - endTime[n - 1];
        int ans = 0, s = 0;
        for (int i = 0;i <= n;i++) {
            s += free_t[i];
            if(i < k) {
                continue;
            }
            ans = max(ans,s);
            s -= free_t[i - k];
        }
        return ans;
    }
};

int main() {
    max_free_time3439 ps;
    int eventTime = 5,k = 1;
    vector<int> startTime = {1,3},endTime = {2,5};
    std::cout << ps.maxFreeTime(eventTime,k,startTime,endTime);
    return 0;
}
