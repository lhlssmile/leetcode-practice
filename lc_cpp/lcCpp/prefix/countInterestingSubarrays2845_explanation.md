# LeetCode 2845: 统计趣味子数组 (Count Interesting Subarrays) 解题思路

这道题要求我们统计一个数组 `nums` 中有多少个子数组 `nums[l..r]` 满足特定条件：子数组中满足 `nums[i] % modulo == k` 的元素个数 `cnt`，使得 `cnt % modulo == k`。

## 核心思路：前缀和 + 哈希表 + 模运算

直接暴力枚举所有子数组 `nums[l..r]` 并统计其中满足 `nums[i] % modulo == k` 的元素个数，时间复杂度会达到 O(n^2)，对于 n 较大的情况会超时。我们需要更优化的方法。

我们可以借鉴“子数组和为 K”这类问题的经典解法：**前缀和 + 哈希表**。

1.  **转化问题**:
    我们关心的不是子数组元素的具体值，而是子数组中满足 `nums[i] % modulo == k` 的元素**个数**。
    令 `cnt[l..r]` 表示子数组 `nums[l..r]` 中满足 `nums[i] % modulo == k` 的元素个数。
    题目要求我们找到满足 `cnt[l..r] % modulo == k` 的子数组 `[l, r]` 的数量。

2.  **引入前缀和**:
    定义一个前缀和数组（或者用一个变量 `prefix_sum` 实时计算）`P`，其中 `P[i]` 表示 `nums[0..i-1]` 中满足 `nums[j] % modulo == k` 的元素个数。
    那么，子数组 `nums[l..r]` 中满足条件的元素个数 `cnt[l..r]` 就等于 `P[r+1] - P[l]`。

3.  **利用模运算**:
    我们要找的是满足 `(P[r+1] - P[l]) % modulo == k` 的 `(l, r)` 对。
    根据模运算的性质，这个条件等价于 `P[r+1] % modulo - P[l] % modulo + modulo) % modulo == k`。
    移项得到：`P[l] % modulo == (P[r+1] % modulo - k + modulo) % modulo`。

4.  **使用哈希表优化**:
    当我们遍历到 `nums[r]` 时，我们计算出当前的 `prefix_sum = P[r+1]`。
    我们需要找到多少个 `l <= r` 使得 `P[l] % modulo == (prefix_sum % modulo - k + modulo) % modulo`。

    我们可以使用一个哈希表 `count` 来存储**前缀和模 `modulo` 的值**出现的次数。
    `count[x]` 表示值为 `x` 的 `P[i] % modulo` 已经出现了多少次。

    在遍历到 `r` 时：
    a.  计算当前的 `prefix_sum` (即 `P[r+1]`)。
    b.  计算 `need = (prefix_sum % modulo - k + modulo) % modulo`。
    c.  在哈希表 `count` 中查找 `need` 出现的次数，即 `count[need]`。这个次数就是以 `r` 为右端点，满足条件的子数组的数量。将 `count[need]` 加入最终答案 `ans`。
    d.  将当前的 `prefix_sum % modulo` 加入哈希表，即 `count[prefix_sum % modulo]++`。

5.  **初始化**:
    为了处理左边界 `l=0` 的情况（即子数组从 `nums[0]` 开始），我们需要在哈希表中初始化 `count[0] = 1`。这代表一个空前缀 `P[0]`，其值为 0，`P[0] % modulo == 0`。
    当 `(prefix_sum % modulo - k + modulo) % modulo == 0` 时，`count[0]` 就能正确处理从索引 0 开始的子数组。

## C++ 代码解析

```cpp
#include <bits/stdc++.h> // 引入常用头文件
#include <vector>      // 引入 vector
#include <unordered_map> // 引入哈希表

using namespace std;

class countInterestingSubarrays2845 {
public:
    using ll = long long; // 使用 long long 存储结果，防止溢出

    ll countInterestingSubarrays(vector<int>& nums, int modulo, int k) { // 注意 LeetCode 原始函数签名 modulo 在前
        // unordered_map<int, ll> count; // 哈希表，存储 <前缀和 % modulo, 出现次数>
        // LeetCode 提供的 C++ 代码中使用了 std::pmr::unordered_map，功能类似，但使用了多态内存资源
        std::pmr::unordered_map<int, ll> count;

        count[0] = 1; // 初始化，处理 l=0 的情况，空前缀和模 modulo 为 0
        ll ans = 0;         // 结果
        int prefix_sum = 0; // 当前的前缀和（满足 num % modulo == k 的元素个数）

        for (int num : nums) { // 遍历数组
            if (num % modulo == k) { // 如果当前元素满足条件
                prefix_sum++;      // 前缀和加 1
            }

            // 计算我们需要的前一个前缀和模 modulo 的值
            // P[l] % modulo == (P[r+1] % modulo - k % modulo + modulo) % modulo
            // 注意：题目给的 k 可能大于等于 modulo，所以 k 也需要取模
            int need = (prefix_sum - k % modulo + modulo) % modulo;
            // 修正 C++ 代码中的小笔误，原始代码是 (prefix_sum - k)，应该是 (prefix_sum - k % modulo)
            // 并且原始代码的 modulo 和 k 参数位置与 LeetCode 不同，这里按照 LeetCode 调整

            // 查找哈希表中是否存在需要的 need 值
            if (count.count(need)) {
                ans += count[need]; // 如果存在，将对应的次数加到结果中
            }

            // 将当前的前缀和模 modulo 加入哈希表
            count[prefix_sum % modulo]++;
        }
        return ans;
    }
};

// --- 以下是你提供的 main 函数，用于本地测试 ---
#include <iostream>
int main(){
    vector<int> nums = {3, 1, 9, 6};
    int modulo = 3;
    int k = 0;
    countInterestingSubarrays2845 c;
    // 注意调用时参数顺序与 LeetCode 保持一致
    cout << c.countInterestingSubarrays(nums, modulo, k) << endl; // 预期输出 2

    vector<int> nums2 = {3, 2, 4};
    int modulo2 = 2;
    int k2 = 1;
    cout << c.countInterestingSubarrays(nums2, modulo2, k2) << endl; // 预期输出 3
    return 0;
}
```

**注意:**

*   你的原始 C++ 代码中 `countInterestingSubarrays` 函数的参数顺序 `(vector<int>& nums, int k, int modulo)` 与 LeetCode 官方题目 `(vector<int>& nums, int modulo, int k)` 不同，我在解释和代码中已按照 LeetCode 的顺序进行了调整和说明。
*   计算 `need` 时，`k` 也应该对 `modulo` 取模，即 `(prefix_sum - k % modulo + modulo) % modulo`，你的原始代码是 `(prefix_sum - k) % modulo`，这在 `k >= modulo` 时会有问题。我在解释和代码中已修正。
*   你的原始 C++ 代码没有初始化 `count[0] = 1`，这会导致缺少从索引 0 开始的满足条件的子数组。我在解释和代码中已添加。

## 总结

这类统计满足特定条件的子数组个数的问题，特别是条件与子数组元素的**和**或**个数**相关时，通常可以考虑使用**前缀和**技巧。

当条件涉及到**模运算**时（例如子数组和模 K 等于某个值，或者像本题这样元素个数模 modulo 等于 k），结合**哈希表**来存储前缀和（或前缀和模 K）出现的次数，可以有效地将查找配对前缀和的时间复杂度从 O(n) 降低到 O(1)（平均情况），从而将整体时间复杂度优化到 O(n)。

关键在于将子数组的条件 `Condition(l, r)` 转化为关于前缀和 `P[r+1]` 和 `P[l]` 的等式或关系式，然后利用哈希表快速查找满足条件的 `P[l]`。