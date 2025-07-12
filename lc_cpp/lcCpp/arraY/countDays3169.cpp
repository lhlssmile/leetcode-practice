//
// Created by 24276 on 2025/7/12.
//
#include <vector>
#include <algorithm>  // 改为标准头文件
#include <iostream>
#include <tuple>      // 添加tuple支持
using namespace std;

class count_days3169 {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        // 合并区间
        if (meetings.size() == 0) {
            return days;
        }

        // 使用标准sort而不是ranges::sort
        sort(meetings.begin(), meetings.end());

        int start = meetings[0][0], end = meetings[0][1];
        int occupied_days = 0;

        for (int i = 1; i < meetings.size(); i++) {
            if (meetings[i][0] <= end) {
                // 合并区间
                end = max(end, meetings[i][1]);
            } else {
                // 计算当前区间占用的天数
                occupied_days += end - start + 1;
                start = meetings[i][0];
                end = meetings[i][1];
            }
        }

        // 计算最后一个区间占用的天数
        occupied_days += end - start + 1;

        return days - occupied_days;
    }
};

int main() {
    int days = 10;
    vector<vector<int>> meetings = {
        {5,7},{1,3},{9,10}
    };
    count_days3169 ps;
    int result = ps.countDays(days, meetings);
    cout << "Result: " << result << endl;  // 添加输出
    vector<vector<int>> meetings1 = {
        {2,4},{1,3}
    };
    int days1 = 6;
    ps.countDays(days1,meetings1);
    return 0;
}