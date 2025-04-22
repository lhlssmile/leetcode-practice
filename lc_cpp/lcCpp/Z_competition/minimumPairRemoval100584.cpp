//
// Created by 24276 on 2025/4/6.
//
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class minimum_pair_removal100584 {
public:
    int minimumPairRemoval(vector<int>& nums) {
        list<int> arr(nums.begin(), nums.end());
        int operations = 0;

        while (arr.size() > 1) {
            // 检查是否已经是非递减的
            bool isSorted = true;
            auto it = arr.begin();
            //先给prev赋值it 然后移动it
            auto prev = it++;

            while (it != arr.end()) {
                if (*it < *prev) {
                    isSorted = false;
                    break;
                }
                prev = it++;
            }

            if (isSorted) {
                return operations;
            }

            // 找到和最小的相邻元素对
            int minSum = INT_MAX;
            list<int>::iterator minPos;

            auto it1 = arr.begin();
            for (auto it2 = next(arr.begin()); it2 != arr.end(); ++it1, ++it2) {
                int sum = *it1 + *it2;
                if (sum < minSum) {
                    minSum = sum;
                    minPos = it1;
                }
            }

            // 合并元素
            *minPos = minSum;
            arr.erase(next(minPos));

            operations++;
        }

        return operations;
    }

    int minimumPairRemovalRe(vector<int>& nums) {
        list<int> arr(nums.begin(),nums.end());
        int operations = 0;
        while(arr.size() > 1) {
            auto isSorted = true;
            auto curr = arr.begin();
            auto prev = curr++;
            while (curr != arr.end()) {
                if (*curr < *prev) {
                    isSorted = false;
                    break;
                }
                prev = curr++;
            }
            if (isSorted) {
                return operations;
            }
            int minSum = INT_MAX;
            list<int>::iterator minPos; //不止一个最小和   取最左边
            auto it1 = arr.begin();
            for(auto it2 = next(arr.begin());
                it2 != arr.end();it1++,it2++) {
                int sum = *it1 + *it2;
                if (sum < minSum) {
                    minSum = sum;
                    minPos = it1;
                }
            }
            *minPos = minSum;
            arr.erase(next(minPos));
            operations++;
        }
        return operations;
    }
};

int main() {
    minimum_pair_removal100584 solution;
    vector<int> nums = {5,2,3,1};
    cout << solution.minimumPairRemoval(nums);
    return 0;
}
