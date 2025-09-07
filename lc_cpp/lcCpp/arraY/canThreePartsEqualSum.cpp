#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& arr) {
        int sum = 0;
        for (int v : arr) {
            sum += v;
        }
        if (sum % 3 != 0) {
            return false;
        }
        
        int part = 0, currentSum = 0;
        
        for (int x : arr) {
            currentSum += x;
            if (currentSum == sum / 3) {
                currentSum = 0;
                part++;
            }
        }
        return part >= 3;
    }
};

// 测试函数
void testCanThreePartsEqualSum() {
    Solution solution;
    
    cout << "=== LeetCode 1013: 将数组分成和相等的三个部分 ===" << endl;
    
    // 测试用例1
    vector<int> arr1 = {0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1};
    bool result1 = solution.canThreePartsEqualSum(arr1);
    cout << "测试用例1: [0,2,1,-6,6,7,9,-1,2,0,1] -> 结果: " << (result1 ? "true" : "false") << endl;
    
    // 测试用例2
    vector<int> arr2 = {0, 2, 1, -6, 6, 6, 7, 9, -1, 2, 0, 1};
    bool result2 = solution.canThreePartsEqualSum(arr2);
    cout << "测试用例2: [0,2,1,-6,6,6,7,9,-1,2,0,1] -> 结果: " << (result2 ? "true" : "false") << endl;
    
    // 测试用例3
    vector<int> arr3 = {3, 3, 3};
    bool result3 = solution.canThreePartsEqualSum(arr3);
    cout << "测试用例3: [3,3,3] -> 结果: " << (result3 ? "true" : "false") << endl;
    
    // 测试用例4
    vector<int> arr4 = {1, 1, 1, 1};
    bool result4 = solution.canThreePartsEqualSum(arr4);
    cout << "测试用例4: [1,1,1,1] -> 结果: " << (result4 ? "true" : "false") << endl;
    
    // 测试用例5
    vector<int> arr5 = {0, 0, 0, 0};
    bool result5 = solution.canThreePartsEqualSum(arr5);
    cout << "测试用例5: [0,0,0,0] -> 结果: " << (result5 ? "true" : "false") << endl;
}

int main() {
    testCanThreePartsEqualSum();
    return 0;
}

/*
算法说明:
1. 首先计算数组总和，如果不能被3整除则返回false
2. 遍历数组，累加当前和
3. 当累加和等于目标值(sum/3)时，重置累加和并增加部分计数
4. 最终检查是否找到至少3个部分

时间复杂度: O(n)
空间复杂度: O(1)
*/