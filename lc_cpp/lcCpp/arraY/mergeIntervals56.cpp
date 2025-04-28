#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
class merge_intervals56 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        /**
         *  {1,3},{2,6},{8,10}     怎么才满足可以合并?
         */
        //题目没有表明 子区间是否都是升序?sort n个只有2个元素的一维数组?效率
        if(intervals.empty()) return {};
        std::sort(intervals.begin(),intervals.end(),
            [](const std::vector<int>& a,const std::vector<int>& b) {
                return a[0] < b[0];
            });
        vector<vector<int>> result;
        int start = intervals[0][0];
        int end = intervals[0][1];

        for(int i = 1;i < intervals.size();++i) {
            if(intervals[i][0] <= end) {
                //ex:   {1,6},{2,4}
                end = std::max(intervals[i][1],end);
            }else {
                result.push_back({start,end});
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }
        result.push_back({start,end});
        return result;
    }
};

int main() {
    merge_intervals56 ps;
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    auto res = ps.merge(intervals);
    for(auto const vector : res) {
        cout << "[";
        for(auto const ele : vector) {
            cout << ele << " ";
        }
        cout << "]";
    }
    return 0;
}
