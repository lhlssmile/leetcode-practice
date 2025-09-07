#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

ll prefix(ll n) {
    ll ans = 0;
    ll base = 1;
    int k = 1;

    while (true) {
        ll nextBase = base * 4;
        ll L = base;
        ll R = nextBase - 1;
        if (n >= R) {
            ans += (R - L + 1) * 1LL * k;
        } else {
            ans += (n - L + 1) * 1LL * k;
            break;
        }
        base = nextBase;
        k++;
    }
    return ans;
}

class Solution {
public:
    long long minOperations(std::vector<std::vector<int>>& queries) {
        ll total = 0;
        for (auto& q : queries) {
            ll l = q[0], r = q[1];
            ll S = prefix(r) - prefix(l - 1);
            total += (S + 1) / 2;
        }
        return total;
    }
};

// 测试函数
void testMinOperations() {
    Solution solution;
    
    // 测试用例1
    std::vector<std::vector<int>> queries1 = {{1, 4}, {2, 6}, {3, 8}};
    ll result1 = solution.minOperations(queries1);
    std::cout << "测试用例1: ";
    for (const auto& q : queries1) {
        std::cout << "[" << q[0] << ", " << q[1] << "] ";
    }
    std::cout << " -> 结果: " << result1 << std::endl;
    
    // 测试用例2
    std::vector<std::vector<int>> queries2 = {{1, 10}, {5, 15}};
    ll result2 = solution.minOperations(queries2);
    std::cout << "测试用例2: ";
    for (const auto& q : queries2) {
        std::cout << "[" << q[0] << ", " << q[1] << "] ";
    }
    std::cout << " -> 结果: " << result2 << std::endl;
    
    // 测试用例3
    std::vector<std::vector<int>> queries3 = {{1, 1}, {2, 2}, {3, 3}};
    ll result3 = solution.minOperations(queries3);
    std::cout << "测试用例3: ";
    for (const auto& q : queries3) {
        std::cout << "[" << q[0] << ", " << q[1] << "] ";
    }
    std::cout << " -> 结果: " << result3 << std::endl;
    
    // 测试prefix函数
    std::cout << "\nprefix函数测试:" << std::endl;
    for (int i = 1; i <= 10; i++) {
        std::cout << "prefix(" << i << ") = " << prefix(i) << std::endl;
    }
}

int main() {
    std::cout << "=== LeetCode 最小操作数问题 ===" << std::endl;
    testMinOperations();
    return 0;
}

/*
算法说明:
1. prefix(n)函数计算从1到n的前缀和
2. 使用base和k来计算每个区间的贡献
3. 对于每个查询[l,r]，计算prefix(r) - prefix(l-1)
4. 最终结果是(S+1)/2

时间复杂度: O(Q * log(max(r)))，其中Q是查询数量
空间复杂度: O(1)
*/