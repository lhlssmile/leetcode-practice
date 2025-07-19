//
// Created by 24276 on 2025/7/19.
//
/**
*你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。



示例 1：

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
示例 2：

输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。


提示：

1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
prerequisites[i] 中的所有课程对 互不相同
 */
#include <vector>
#include <queue>
#include <iostream>
#include <functional>
using namespace std;
class can_finish {
public:
    // 方法1：DFS检测环（递归）
    bool canFinish_dfs(int numCourses, vector<vector<int>>& prerequisites) {
        // 构建邻接表
        vector<vector<int>> graph(numCourses);
        for (auto& pre : prerequisites) {
            graph[pre[1]].push_back(pre[0]); // pre[1] -> pre[0]
        }
        
        // 0: 未访问, 1: 正在访问, 2: 已完成
        vector<int> state(numCourses, 0);
        
        function<bool(int)> dfs = [&](int course) -> bool {
            if (state[course] == 1) return false; // 发现环
            if (state[course] == 2) return true;  // 已访问过
            
            state[course] = 1; // 标记为正在访问
            
            for (int next : graph[course]) {
                if (!dfs(next)) return false;
            }
            
            state[course] = 2; // 标记为已完成
            return true;
        };
        
        // 检查每个节点
        for (int i = 0; i < numCourses; i++) {
            if (state[i] == 0 && !dfs(i)) {
                return false;
            }
        }
        
        return true;
    }
    
    // 方法2：BFS拓扑排序（Kahn算法）
    bool canFinish_bfs(int numCourses, vector<vector<int>>& prerequisites) {
        // 构建邻接表和入度数组
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for (auto& pre : prerequisites) {
            graph[pre[1]].push_back(pre[0]);
            indegree[pre[0]]++;
        }
        
        // 将入度为0的节点加入队列
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int processed = 0;
        
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            processed++;
            
            // 处理所有后继节点
            for (int next : graph[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return processed == numCourses;
    }
    
    // 方法3：优化的DFS（使用栈模拟递归）
    bool canFinish_iterative(int numCourses, vector<vector<int>>& prerequisites) {
        // 构建邻接表
        vector<vector<int>> graph(numCourses);
        for (auto& pre : prerequisites) {
            graph[pre[1]].push_back(pre[0]);
        }
        
        vector<int> color(numCourses, 0); // 0: 白色, 1: 灰色, 2: 黑色
        
        for (int i = 0; i < numCourses; i++) {
            if (color[i] == 0) {
                vector<int> stack = {i};
                
                while (!stack.empty()) {
                    int node = stack.back();
                    
                    if (color[node] == 0) {
                        color[node] = 1; // 标记为灰色
                        
                        for (int neighbor : graph[node]) {
                            if (color[neighbor] == 1) {
                                return false; // 发现环
                            }
                            if (color[neighbor] == 0) {
                                stack.push_back(neighbor);
                            }
                        }
                    } else {
                        stack.pop_back();
                        color[node] = 2; // 标记为黑色
                    }
                }
            }
        }
        
        return true;
    }
    
    // 主方法（推荐使用BFS拓扑排序）
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        return canFinish_bfs(numCourses, prerequisites);
    }
};

int main() {
    can_finish solution;
    
    // 测试用例1
    vector<vector<int>> prerequisites1 = {{1, 0}};
    int numCourses1 = 2;
    
    cout << "测试用例1 (numCourses=2, prerequisites=[[1,0]]):" << endl;
    cout << "DFS检测环: " << (solution.canFinish_dfs(numCourses1, prerequisites1) ? "true" : "false") << endl;
    cout << "BFS拓扑排序: " << (solution.canFinish_bfs(numCourses1, prerequisites1) ? "true" : "false") << endl;
    cout << "迭代DFS: " << (solution.canFinish_iterative(numCourses1, prerequisites1) ? "true" : "false") << endl;
    
    // 测试用例2
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    int numCourses2 = 2;
    
    cout << "\n测试用例2 (numCourses=2, prerequisites=[[1,0],[0,1]]):" << endl;
    cout << "DFS检测环: " << (solution.canFinish_dfs(numCourses2, prerequisites2) ? "true" : "false") << endl;
    cout << "BFS拓扑排序: " << (solution.canFinish_bfs(numCourses2, prerequisites2) ? "true" : "false") << endl;
    cout << "迭代DFS: " << (solution.canFinish_iterative(numCourses2, prerequisites2) ? "true" : "false") << endl;
    
    // 测试用例3（更复杂的情况）
    vector<vector<int>> prerequisites3 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    int numCourses3 = 4;
    
    cout << "\n测试用例3 (numCourses=4, prerequisites=[[1,0],[2,0],[3,1],[3,2]]):" << endl;
    cout << "DFS检测环: " << (solution.canFinish_dfs(numCourses3, prerequisites3) ? "true" : "false") << endl;
    cout << "BFS拓扑排序: " << (solution.canFinish_bfs(numCourses3, prerequisites3) ? "true" : "false") << endl;
    cout << "迭代DFS: " << (solution.canFinish_iterative(numCourses3, prerequisites3) ? "true" : "false") << endl;
    
    return 0;
}

/*
=== 课程调度问题 - 拓扑排序经典应用 ===

【题目本质】
- 判断有向图是否存在环（环检测问题）
- 如果无环，则可以完成所有课程（DAG - 有向无环图）
- 如果有环，则存在循环依赖，无法完成

【三种经典解法对比】

1. DFS检测环（递归版本）
   - 核心思想：使用三色标记法检测环
   - 白色(0)：未访问
   - 灰色(1)：正在访问（在当前DFS路径中）
   - 黑色(2)：已完成访问
   - 环检测：如果访问到灰色节点，说明存在环
   - 时间复杂度：O(V + E)
   - 空间复杂度：O(V) 递归栈
   - 优点：直观易懂，经典算法
   - 缺点：递归深度可能导致栈溢出

2. BFS拓扑排序（Kahn算法）
   - 核心思想：不断移除入度为0的节点
   - 算法步骤：
     1) 计算所有节点的入度
     2) 将入度为0的节点加入队列
     3) 不断取出队列中的节点，减少其邻接节点的入度
     4) 如果新的节点入度变为0，加入队列
     5) 最后检查是否处理了所有节点
   - 时间复杂度：O(V + E)
   - 空间复杂度：O(V)
   - 优点：迭代实现，不会栈溢出，同时可以得到拓扑序列
   - 缺点：需要额外的入度数组

3. 迭代DFS（栈模拟递归）
   - 核心思想：用栈模拟递归过程，避免栈溢出
   - 同样使用三色标记法
   - 手动管理栈，控制访问顺序
   - 时间复杂度：O(V + E)
   - 空间复杂度：O(V)
   - 优点：避免递归栈溢出，保持DFS的逻辑
   - 缺点：实现相对复杂

【关键技巧】

1. 图的构建
   - prerequisites[i] = [ai, bi] 表示 bi -> ai
   - 注意依赖关系的方向：要学ai必须先学bi

2. 环检测的本质
   - DFS中遇到"正在访问"的节点 = 发现后向边 = 存在环
   - BFS中无法处理完所有节点 = 存在环

3. 算法选择建议
   - 一般情况：推荐BFS拓扑排序（Kahn算法）
   - 需要拓扑序列：必须用BFS
   - 图规模很大：考虑迭代DFS避免栈溢出
   - 学习理解：从递归DFS开始

【扩展应用】
1. 课程调度II：返回具体的课程学习顺序
2. 编译依赖：检查模块编译顺序
3. 任务调度：检查任务依赖关系
4. 死锁检测：检查资源依赖环

【复杂度分析】
- V: 课程数量（节点数）
- E: 先修关系数量（边数）
- 所有方法的时间复杂度都是 O(V + E)
- 空间复杂度都是 O(V)，主要用于存储图和辅助数组

【测试用例分析】
- 用例1：[[1,0]] → 0->1，无环，可完成
- 用例2：[[1,0],[0,1]] → 0->1->0，有环，不可完成
- 用例3：[[1,0],[2,0],[3,1],[3,2]] → 复杂DAG，无环，可完成
*/
