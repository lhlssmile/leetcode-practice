//
// Created by 24276 on 2025/4/12.
//

#include <bitset>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <ranges>
using namespace std;

const int MAX_XOR = 200005;
class unique_xor_triplets100628 {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> unique_xors;

        // 对于所有可能的 j 和 k 对，计算 nums[j] ^ nums[k]
        for (int i = 0; i < n; i++) {
            unordered_set<int> two_xors;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    two_xors.insert(nums[i] ^ nums[j]);
                }
            }

            // 将 nums[i] 与所有可能的 two_xors 异或
            for (const int& xor_val : two_xors) {
                for (int k = 0; k < n; k++) {
                    if (i != k) {
                        unique_xors.insert(xor_val ^ nums[k]);
                    }
                }
            }
        }

        return unique_xors.size();
    }
    int uniqueXorTripletsA(vector<int>& nums) {
        int n = nums.size();
        bitset<MAX_XOR> xor_exists; // 用 bitset 记录最终异或值
        vector<int> two_xor_freq(MAX_XOR, 0); // 用数组记录 nums[j] XOR nums[k] 的频率

        // 枚举 j, k 满足 j <= k
        for (int j = 0; j < n; ++j) {
            for (int k = j; k < n; ++k) {
                int xor_val = nums[j] ^ nums[k];
                two_xor_freq[xor_val]++;
            }
        }

        // 枚举 i 和可能的 two_xor 值
        for (int i = 0; i < n; ++i) {
            for (int xor_val = 0; xor_val < MAX_XOR; ++xor_val) {
                if (two_xor_freq[xor_val] > 0) {
                    xor_exists[nums[i] ^ xor_val] = 1; // 标记最终异或值
                }
            }
        }

        return xor_exists.count(); // 返回不同异或值的数量
    }
    int uniqueXor(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return n;
        }
        return bit_floor(nums.size()) << 1;
    }
    int uniqueXor3514(vector<int>& nums){
        //两次On^2 第三次长度为n 前两次最多为u
        int n = nums.size();
        //bit_width 是 C++20 引入的函数（<bit> 头文件），
        //返回无符号整数的二进制表示中最高位 1 的位置（从 1 开始计数）。
        //此案例max num = 3 -> 11(binary) 最高位1位置位2（下标）
        int u = 1 << bit_width((unsigned) ranges::max(nums));
        cout << ranges::max(nums) << " " << u;
        cout << bit_width((unsigned) ranges::max(nums));
        vector<int> has(u);
        for (int i = 0;i < n;i++) {
            for(int j = i;j < n;j++) {
                has[nums[i] ^ nums[j]] = true;
            }
        }
        vector<int> has3(u);
        for (int xy = 0;xy < u;xy++) {
            if (has[xy]) {
                for (int z : nums) {
                    has3[xy ^ z] = true;
                }
            }
        }
        return reduce(has3.begin(),has3.end());
    }
};

int main() {
    unique_xor_triplets100628 sol;
    vector<int> nums = {6,7,8,9};
    cout << sol.uniqueXor3514(nums);
    return 0;
}
