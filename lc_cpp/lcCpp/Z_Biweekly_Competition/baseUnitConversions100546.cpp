#include <functional>
#include <vector>
#include <iostream>

using namespace std;

/**
 * 有 n 种单位，编号从 0 到 n - 1。给你一个二维整数数组 conversions，长度为 n - 1，其中 conversions[i] = [sourceUniti, targetUniti, conversionFactori] ，表示一个 sourceUniti 类型的单位等于 conversionFactori 个 targetUniti 类型的单位。

请你返回一个长度为 n 的数组 baseUnitConversion，其中 baseUnitConversion[i] 表示 一个 0 类型单位等于多少个 i 类型单位。由于结果可能很大，请返回每个 baseUnitConversion[i] 对 109 + 7 取模后的值。

 

示例 1：

输入： conversions = [[0,1,2],[1,2,3]]

输出： [1,2,6]

解释：

使用 conversions[0]：将一个 0 类型单位转换为 2 个 1 类型单位。
使用 conversions[0] 和 conversions[1] 将一个 0 类型单位转换为 6 个 2 类型单位。

示例 2：

输入： conversions = [[0,1,2],[0,2,3],[1,3,4],[1,4,5],[2,5,2],[4,6,3],[5,7,4]]

输出： [1,2,3,8,10,6,30,24]

解释：

使用 conversions[0] 将一个 0 类型单位转换为 2 个 1 类型单位。
使用 conversions[1] 将一个 0 类型单位转换为 3 个 2 类型单位。
使用 conversions[0] 和 conversions[2] 将一个 0 类型单位转换为 8 个 3 类型单位。
使用 conversions[0] 和 conversions[3] 将一个 0 类型单位转换为 10 个 4 类型单位。
使用 conversions[1] 和 conversions[4] 将一个 0 类型单位转换为 6 个 5 类型单位。
使用 conversions[0]、conversions[3] 和 conversions[5] 将一个 0 类型单位转换为 30 个 6 类型单位。
使用 conversions[1]、conversions[4] 和 conversions[6] 将一个 0 类型单位转换为 24 个 7 类型单位。
 

 2 <= n <= 105
conversions.length == n - 1
0 <= sourceUniti, targetUniti < n
1 <= conversionFactori <= 109
保证单位 0 可以通过 唯一 的转换路径（不需要反向转换）转换为任何其他单位。
 * 解题思路：
 * 1. 这道题可以看作是一个有向无环图(DAG)的问题，其中每个单位是一个节点，转换关系是边
 * 2. 题目保证单位0可以通过唯一路径转换到其他单位，说明这是一个树形结构
 * 3. 我们可以从单位0开始进行深度优先搜索(DFS)
 * 4. 对于每个单位i，我们需要计算从单位0到单位i的转换系数
 * 5. 由于结果可能很大，需要对10^9+7取模
 * 
 * 具体实现：
 * 1. 首先构建邻接表，记录每个单位的转换关系
 * 2. 使用DFS遍历所有单位，从单位0开始
 * 3. 对于每个单位，根据其父单位的转换系数计算当前单位的转换系数
 * 4. 使用动态规划的思想，避免重复计算
 * 
 * 时间复杂度：O(n)，其中n是单位的数量
 * 空间复杂度：O(n)，用于存储邻接表和结果数组
 * 
 * DFS实现步骤：
 * 1. 构建邻接表，使用vector<vector<pair<int,int>>>存储，pair中first是目标单位，second是转换系数
 * 2. 创建结果数组res，初始时res[0] = 1
 * 3. 从单位0开始DFS，对于每个单位u：
 *    - 遍历其所有邻居v
 *    - 计算v的转换系数：res[v] = res[u] * conversionFactor % MOD
 *    - 递归处理v
 * 4. 最后返回res数组
 */
class baseUnitConversions100546{
public:
    vector<int> baseUnitConversions(vector<vector<int>>& conversions){
        const int MOD = 1e9 + 7;
        int n = conversions.size() + 1;
        vector<vector<pair<int,int>>> graph(n);
        
        // 构建邻接表
        for(auto& conv : conversions){
            int u = conv[0], v = conv[1], factor = conv[2];
            graph[u].emplace_back(v, factor);
        }
        
        vector<int> res(n);
        res[0] = 1;  // 单位0的转换系数为1
        
        // DFS函数
        function<void(int)> dfs = [&](int u){
            for(auto& [v, factor] : graph[u]){
                res[v] = (long long)res[u] * factor % MOD;
                dfs(v);
            }
        };
        
        dfs(0);
        return res;
    }
    
    vector<int> baseUnitConversionsa(vector<vector<int>>& conversions) {
        //DFS 
        /**
            ex:1个0单位 -> 2个1单位
                1个1单位 -> 3个2单位
        */
        constexpr int MOD = 1e9 + 7;
        //创建邻接表。
        int n = conversions.size() + 1;
        vector<vector<pair<int,int>>> graph(n);
        for (auto const& conv : conversions) {
            int base_unit = conv[0],target_unit = conv[1],conversion_factor = conv[2];
            graph[base_unit].emplace_back(target_unit,conversion_factor);
        }
        vector<int > ans(n);
        ans[0] = 1;
        auto dfs = [&](this auto&& dfs,int __base__unit__) -> void {
            for(auto& [target_unit,factor]: graph[__base__unit__]) {
                ans[target_unit] = (long long )ans[__base__unit__] * factor % MOD;
                dfs(target_unit);
            }
        };
        dfs(0);
        return ans;
    }
};
int main(){
    baseUnitConversions100546 sol;
    vector<vector<int>> conversions = {
        {0,1,2},{1,2,3}
    };
    auto res = sol.baseUnitConversionsa(conversions);
    for (int ele : res) {
        cout << ele << " ";
    }
}