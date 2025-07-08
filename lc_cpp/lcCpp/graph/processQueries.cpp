//
// Created by 24276 on 2025/7/6.
//
/**
*给你一个整数 c，表示 c 个电站，每个电站有一个唯一标识符 id，从 1 到 c 编号。

这些电站通过 n 条 双向 电缆互相连接，表示为一个二维数组 connections，其中每个元素 connections[i] = [ui, vi] 表示电站 ui 和电站 vi 之间的连接。直接或间接连接的电站组成了一个 电网 。

最初，所有 电站均处于在线（正常运行）状态。

另给你一个二维数组 queries，其中每个查询属于以下 两种类型之一 ：

[1, x]：请求对电站 x 进行维护检查。如果电站 x 在线，则它自行解决检查。如果电站 x 已离线，则检查由与 x 同一 电网 中 编号最小 的在线电站解决。如果该电网中 不存在 任何 在线 电站，则返回 -1。

[2, x]：电站 x 离线（即变为非运行状态）。

返回一个整数数组，表示按照查询中出现的顺序，所有类型为 [1, x] 的查询结果。

注意：电网的结构是固定的；离线（非运行）的节点仍然属于其所在的电网，且离线操作不会改变电网的连接性。

  

示例 1：

输入： c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]

输出： [3,2,3]

解释：



最初，所有电站 {1, 2, 3, 4, 5} 都在线，并组成一个电网。
查询 [1,3]：电站 3 在线，因此维护检查由电站 3 自行解决。
查询 [2,1]：电站 1 离线。剩余在线电站为 {2, 3, 4, 5}。
查询 [1,1]：电站 1 离线，因此检查由电网中编号最小的在线电站解决，即电站 2。
查询 [2,2]：电站 2 离线。剩余在线电站为 {3, 4, 5}。
查询 [1,2]：电站 2 离线，因此检查由电网中编号最小的在线电站解决，即电站 3。
示例 2：

输入： c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]

输出： [1,-1]

解释：

没有连接，因此每个电站是一个独立的电网。
查询 [1,1]：电站 1 在线，且属于其独立电网，因此维护检查由电站 1 自行解决。
查询 [2,1]：电站 1 离线。
查询 [1,1]：电站 1 离线，且其电网中没有其他电站，因此结果为 -1。
  

提示：

1 <= c <= 105
0 <= n == connections.length <= min(105, c * (c - 1) / 2)
connections[i].length == 2
1 <= ui, vi <= c
ui != vi
1 <= queries.length <= 2 * 105
queries[i].length == 2
queries[i][0] 为 1 或 2。
1 <= queries[i][1] <= c©leetcode
 */
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
using namespace std;

class process_queries {
public:
    vector<int> processQueries(int c,
        vector<vector<int>>& connections,
        vector<vector<int>>& queries) {
        
        // 构建邻接表
        vector<vector<int>> graph(c + 1);
        for (auto& conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }
        
        // 预处理：找到每个节点所属的连通分量
        vector<int> component(c + 1, -1);
        vector<vector<int>> components;
        
        for (int i = 1; i <= c; i++) {
            if (component[i] == -1) {
                vector<int> comp;
                dfs(graph, i, component, comp, components.size());
                components.push_back(comp);
            }
        }
        
        // 为每个连通分量维护在线节点的有序集合
        vector<set<int>> onlineNodes(components.size());
        for (int i = 0; i < components.size(); i++) {
            for (int node : components[i]) {
                onlineNodes[i].insert(node);
            }
        }
        
        vector<int> result;
        
        for (auto& query : queries) {
            int type = query[0];
            int station = query[1];
            
            if (type == 1) {
                // 查询操作
                int comp_id = component[station];
                if (onlineNodes[comp_id].count(station)) {
                    // 电站在线，自己处理
                    result.push_back(station);
                } else {
                    // 电站离线，找最小在线电站
                    if (onlineNodes[comp_id].empty()) {
                        result.push_back(-1);
                    } else {
                        result.push_back(*onlineNodes[comp_id].begin());
                    }
                }
            } else if (type == 2) {
                // 离线操作
                int comp_id = component[station];
                onlineNodes[comp_id].erase(station);
            }
        }
        
        return result;
    }
    
private:
    void dfs(vector<vector<int>>& graph, int node, vector<int>& component, 
             vector<int>& comp, int comp_id) {
        component[node] = comp_id;
        comp.push_back(node);
        
        for (int neighbor : graph[node]) {
            if (component[neighbor] == -1) {
                dfs(graph, neighbor, component, comp, comp_id);
            }
        }
    }
};

int main() {
    process_queries ps;
    
    // 测试示例1
    int c1 = 5;
    vector<vector<int>> connections1 = {{1,2},{2,3},{3,4},{4,5}};
    vector<vector<int>> queries1 = {{1,3},{2,1},{1,1},{2,2},{1,2}};
    
    auto result1 = ps.processQueries(c1, connections1, queries1);
    cout << "示例1结果: ";
    for (int x : result1) {
        cout << x << " ";
    }
    cout << endl; // 期望输出: 3 2 3
    
    // 测试示例2
    int c2 = 3;
    vector<vector<int>> connections2 = {};
    vector<vector<int>> queries2 = {{1,1},{2,1},{1,1}};
    
    auto result2 = ps.processQueries(c2, connections2, queries2);
    cout << "示例2结果: ";
    for (int x : result2) {
        cout << x << " ";
    }
    cout << endl; // 期望输出: 1 -1
    
    return 0;
}