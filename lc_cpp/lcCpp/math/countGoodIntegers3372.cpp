#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <ranges>
using namespace std;
class count_good_integers3372 {
public:
    long long countGoodIntegers(int n,int k) {
        //保存阶乘
        vector<int> factorial(n + 1);
        factorial[0] = 1;
        for(int i = 1;i <= n;i++) {
            factorial[i] = factorial[i - 1] * i;
        }

        //枚举左半部分
        long long ans = 0;
        //幂 ex:n = 3 {1~999} 左半部分为 十位数{1,99}            n = 5?  (n - 1) /2 = 2 i =base = 100;i < 1000
        int base = std::pow(10,(n - 1) / 2);
        //first:迭代器 second:true,false 如果是false证明已经存在
        unordered_set<string> vis;
        //ex:在这里枚举10~99
        for(int i = base;i < base * 10;i++ ) {
            string s = to_string(i);
            s += string(s.rbegin() + (n % 2),s.rend());
            if (stoll(s) % k) {
                continue;
            }
            //排序s
            ranges::sort(s);
            //如果 second 是 false（即插入失败，s 已存在），就执行 continue，跳过当前循环的剩余部分。
            if (!vis.insert(s).second) {
                continue;       //不要重复统计
            }
            int cnt[10]{};
            for (char c : s) {
                cnt[c - '0']++;     //统计出现次数
            }
            int res = (n - cnt[0]) * factorial[n - 1];
            for (int c : cnt) {
                res /= factorial[c];
            }
            ans += res;
        }
        return ans;
    }
};

int main() {
    count_good_integers3372 sol;
    std::cout << sol.countGoodIntegers(3, 5) << std::endl; // 输出27
    return 0;
}