#include <vector>
#include <iostream>
using namespace std;
class longest_cycle2360 {
public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<bool> visited(n, false); // 全局访问标记
        vector<bool> inStack(n, false); // 当前DFS路径中的节点
        vector<int> timeStamp(n); // 访问时间戳
        int ans = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(edges, i, 0, visited, inStack, timeStamp, ans);
            }
        }
        return ans;
    }

    int longestCycles(vector<int>& edges) {
        int n = edges.size();
        vector<int> label(n);
        int current_label = 0,ans = -1;
        for(int i = 0;i < n;i++) {
            if(label[i]) {
                continue;
            }
            int pos = i,start_label = current_label;
            while(pos != -1) {
                ++current_label;
                if(label[pos]) {
                    if (label[pos] > start_label) {
                        ans = max(ans,current_label - label[pos]);
                    }
                    break;
                }
                label[pos] = current_label;
                pos = edges[pos];
            }
        }
        return ans;
    }

private:
    void dfs(vector<int>& edges, int node, int time, vector<bool>& visited, 
             vector<bool>& inStack, vector<int>& timeStamp, int& ans) {
        
        if (node == -1) return; // 无出边，退出
        
        if (inStack[node]) { // 在当前DFS路径中发现了环
            ans = max(ans, time - timeStamp[node]);
            return;
        }
        
        if (visited[node]) return; // 已经完全处理过的节点
        
        visited[node] = true;
        inStack[node] = true;
        timeStamp[node] = time;
        
        int next = edges[node];
        dfs(edges, next, time + 1, visited, inStack, timeStamp, ans);
        
        inStack[node] = false; // 回溯时从当前路径中移除
    }
};
int main() {
    longest_cycle2360 solution;
    vector<int> edges = {3, 3, 4, 2, 3};
    cout << solution.longestCycles(edges) << endl; // 输出 3
    return 0;
}