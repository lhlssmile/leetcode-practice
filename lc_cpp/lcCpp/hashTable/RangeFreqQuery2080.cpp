#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
class range_freq_query2080 {
public:

    std::unordered_map<int,vector<int>> positions;
    range_freq_query2080(vector<int>& arr) {
        for(int i = 0; i < arr.size();++i) {
            positions[arr[i]].push_back(i);
        }
    }
    int query(int left,int right,int value) {
        if(positions.find(value) == positions.end()) {
            return 0;
        }
        vector<int> pos = positions[value];
        int left_pos = lower_bound(pos.begin(),pos.end(),left) - pos.begin();
        int right_pos = upper_bound(pos.begin(), pos.end(), right) - pos.begin();

        // 返回区间内的元素数量
        return right_pos - left_pos;
    }
};

int main() {
    vector<int> arr = {12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56};
    range_freq_query2080 obj(arr);

    // 查询结果
    cout << obj.query(1, 2, 4) << endl;  // 输出: 1
    cout << obj.query(0, 11, 33) << endl;  // 输出: 2

    return 0;
}
