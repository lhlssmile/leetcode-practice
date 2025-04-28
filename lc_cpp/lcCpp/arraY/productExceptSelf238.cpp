//
// Created by 24276 on 2025/4/16.
//

#include <vector>
#include <iostream>

using namespace std;
class product_except_self238 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> answer(n,1);
        for (int i = 1;i < n;i++) {
            answer[i] = answer[i - 1] * nums[i - 1];    //前缀乘积
        }
        int suffix = 1;
        for(int i = n - 1;i>=0;i--) {
            answer[i] *= suffix;
            suffix *= nums[i];
        }
        return answer;
    }
    vector<int> productExceptSelfRE(vector<int>& nums) {
        int n = nums.size();
        int zero_count = 0, product = 1;
        vector<int> answer(n, 0);

        // 计算非零元素的乘积
        for (int num : nums) {
            if (num == 0) {
                zero_count++;
                if (zero_count > 1) {
                    return vector<int>(n, 0);  // 多个零，返回全零
                }
            } else {
                product *= num;  // 只乘非零元素
            }
        }

        // 根据零的个数处理
        if (zero_count == 1) {
            for (int i = 0; i < n; i++) {
                if (nums[i] == 0) {
                    answer[i] = product;  // 零位置得非零乘积
                }
            }
        } else if (zero_count == 0) {
            for (int i = 0; i < n; i++) {
                answer[i] = product / nums[i];  // 非零情况，除以自身
            }
        }

        return answer;
    }
};

int main() {
    product_except_self238 sol;
    vector<int> nums = {1,2,3,4};
    auto res = sol.productExceptSelfRE(nums);
    for (int ele : res) {
        cout << ele  << " ";
    }
    return 0;
}
