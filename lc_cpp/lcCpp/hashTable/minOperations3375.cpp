//
// Created by 24276 on 2025/4/9.
//

#include <vector>
#include <iostream>
#include <unordered_set>
using namespace  std;
class min_operations3375 {
public:
    int minOperations(vector<int>& nums,int k) {
        std::unordered_set<int> set(nums.begin(),nums.end());
        int operations = -1;
        for (int node : set) {
            if (node > k) {
                //若全部元素大于k 会修改n - 1次
                operations += 1;
            }
            //最大的数反正只有一个也不用知道是谁,operation少加一次
            if (node < k) {
                return -1;
            }
        }
        return operations + 1;
        // int n = nums.size(),h = 0;
        // for (int i = 0;i < n;i++) {
        //     h = max(h,nums[i]);
        // }
        // //h should be max(nums[i]) started
        // //怎么从第二大的元素开始找？🤔🤔 还是让h直接从max(nums[i])开始?
        // //TODO:不用真的修改数组 只在乎出现的数字. 从second-highest开始 此时大于second-highest的nums[i]全部改为第二高的数字即更新h?
        // //能不能直接记录第二大到k的元素个数?🤔🤔🤔若是nums里包含k就不用加上k
        //
        // return 0;
    }
    int minOp(vector<int>& nums,int k) {
        unordered_set<int> greaterValues;

        for (int num : nums) {
            if (num < k) {
                return -1;  // 有小于k的元素，无法完成
            } else if (num > k) {
                greaterValues.insert(num);  // 收集所有大于k的不同值
            }
        }

        return greaterValues.size();  // 操作次数等于需要操作的不同元素值的数量
    }
};

int main() {
    min_operations3375 solution;
    vector<int> nums = {9,7,5,3};int k = 2;
    cout << solution.minOp(nums,k);
    return 0;
}

