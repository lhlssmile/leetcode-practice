//
// Created by 24276 on 2025/4/8.
//

#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class minimum_operations3396 {
public:
    /**
     * 用set记每个元素最后出现的索引位置 然后三个三个遍历元素?只要当前索引小于最后出现 直接删?
     * @param nums
     * @return
     */
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        int operations = 0;
        unordered_map<int,int> map;
        for (int i = 0;i < n;i++) {
            map[nums[i]] = i;
        }
        //遍历一次数组 如果是中途找到的value和set中所存value的索引 不同 比较大小 若是小于 直接跳至下一个子数组(size = 3)
        int i = 0;
        while(i < n) {
            int window_size = min(3,n - i);
            if (n - i < 3) {
                return i / 3 + 1;
            }
            bool has_duplicate = false;
            unordered_set<int> seen;
            //窗口内是否有重复
            for (int j = i;j < i + window_size;j++) {
                if (seen.count(nums[j])) {
                    has_duplicate = true;
                    break;
                }
                seen.insert(nums[j]);
            }
            //检查窗口内的元素是否在后续出现
            if (!has_duplicate) {
                for (int j = i;j < i + window_size;j++) {
                    if (map[nums[j]] > i + window_size - 1) {
                        has_duplicate = true;
                        break;
                    }
                }
            }
            if (has_duplicate) {
                operations++;
            }
            i += 3;
        }
        return operations;
    }
    int minimumOperation(vector<int>& nums) {
        unordered_set<int> seen;
        for (int i = nums.size() - 1;i >= 0;i--) {
            if (!seen.insert(nums[i]).second) {
                return i / 3 + 1;
            }
        }
        return 0;
    }

};

int main() {
    minimum_operations3396 solution;
    vector<int> nums = {1,2,3,4,2,3,3,5,7};
    cout << solution.minimumOperations(nums);
    return 0;
}
