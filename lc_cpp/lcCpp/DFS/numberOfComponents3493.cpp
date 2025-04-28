//
// Created by 24276 on 2025/4/16.
//

#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

class number_of_components3493 {
public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();
        int ans = 0;
        vector<bool> visited(n, false);  // 使用 vector<bool> 替代 vector<int>

        // 定义 DFS，使用 lambda 表达式
        auto dfs = [&](auto&& dfs, int start_vertex) -> void {
            visited[start_vertex] = true;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && j != start_vertex) {
                    // 判断是否有边：intersect(properties[start_vertex], properties[j]) >= k
                    if (intersect(properties[start_vertex], properties[j]) >= k) {
                        dfs(dfs, j);
                    }
                }
            }
        };

        // 遍历每个节点，计算连通分量
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(dfs, i);
                ans += 1;
            }
        }

        return ans;
    }

private:
    int intersect(vector<int>& a, vector<int>& b) {
        // 将 a 转为集合
        unordered_set<int> set_a(a.begin(), a.end());
        int count = 0;
        // 遍历 b 的每个元素，检查是否在 set_a 中
        for (int num : b) {
            if (set_a.count(num)) {
                count++;
                set_a.erase(num);  // 避免重复计数
            }
        }
        return count;
    }
};

int main() {
    number_of_components3493 sol;
    vector<vector<int>> nums = {{1,2,3},{2,3,4},{4,3,5}};
    int k = 2;
    cout << sol.numberOfComponents(nums,k);
    return 0;
}
