#include <bits/stdc++.h>
#include <vector>

using namespace std;
/**
 * 
 * 给你一个正整数 n，表示一个 n x n 的城市，同时给定一个二维数组 buildings，其中 buildings[i] = [x, y] 表示位于坐标 [x, y] 的一个 唯一 建筑。

如果一个建筑在四个方向（左、右、上、下）中每个方向上都至少存在一个建筑，则称该建筑 被覆盖 。

返回 被覆盖 的建筑数量。

 

示例 1：



输入: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]

输出: 1

解释:

只有建筑 [2,2] 被覆盖，因为它在每个方向上都至少存在一个建筑：
上方 ([1,2])
下方 ([3,2])
左方 ([2,1])
右方 ([2,3])
因此，被覆盖的建筑数量是 1。
 */
class CountCoveredBuildings{
public:
        int countCoveredBuilidings(int n,vector<vector<int>>& buildings){
            if (buildings.size() <= 4) return 0;
            
            // 为每个x坐标和y坐标建立索引
            unordered_map<int, vector<int>> xToY;  // x坐标对应的所有y坐标
            unordered_map<int, vector<int>> yToX;  // y坐标对应的所有x坐标
            
            for (const auto& bd : buildings) {
                int x = bd[0], y = bd[1];
                xToY[x].push_back(y);
                yToX[y].push_back(x);
            }
            
            // 对每个坐标的列表进行排序，方便后续二分查找
            for (auto& [x, ys] : xToY) {
                sort(ys.begin(), ys.end());
            }
            for (auto& [y, xs] : yToX) {
                sort(xs.begin(), xs.end());
            }
            
            int cnt = 0;
            for (const auto& bd : buildings) {
                int x = bd[0], y = bd[1];
                
                // 检查同一行是否有更小和更大的x
                auto& xs = yToX[y];
                auto it = lower_bound(xs.begin(), xs.end(), x);
                bool hasLeft = (it != xs.begin());
                bool hasRight = (it != xs.end() - 1);
                
                // 检查同一列是否有更小和更大的y
                auto& ys = xToY[x];
                auto it2 = lower_bound(ys.begin(), ys.end(), y);
                bool hasUp = (it2 != ys.begin());
                bool hasDown = (it2 != ys.end() - 1);
                
                if (hasLeft && hasRight && hasUp && hasDown) {
                    cnt++;
                }
            }
            
            return cnt;
        }
};
int main(){
    CountCoveredBuildings solution;
    vector<vector<int>> buildings = {{1,2}, {2,2}, {3,2}, {2,1}, {2,3}};
    cout << solution.countCoveredBuilidings(3, buildings) << endl;  // 应该输出1
    return 0;
}