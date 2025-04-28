#include <array>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 51;
int memo[MAXN][MAXN][MAXN * 2];

class cat_mouse_game913 {
public:
    int catMouseGame(vector<vector<int>>& g) {
        const int HOLE = 0;
        int n = g.size();
        vector deg(n, vector<array<int, 2>>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                deg[i][j][0] = g[i].size();
                deg[i][j][1] = g[j].size();
            }
            // 对于猫来说，所有连到洞的边都不能走
            for (int j : g[HOLE]) {
                deg[i][j][1]--;
            }
        }

        vector winner(n, vector<array<int, 2>>(n));
        queue<tuple<int, int, int>> q;
        for (int i = 1; i < n; i++) {
            winner[HOLE][i][1] = 1; // 鼠到达洞中（此时轮到猫移动），鼠获胜
            winner[i][i][0] = winner[i][i][1] = 2; // 猫和鼠出现在同一个节点，无论轮到谁移动，都是猫获胜
            q.emplace(HOLE, i, 1); // 从终点开始倒推
            q.emplace(i, i, 0);
            q.emplace(i, i, 1);
        }

        // 获取 (mouse, cat, turn) 的上个状态（值尚未确定）
        auto get_pre_states = [&](int mouse, int cat, int turn) {
            vector<pair<int, int>> pre_states;
            if (turn == 0) { // 当前轮到鼠移动
                for (int pre_cat : g[cat]) { // 上一轮猫的位置
                    if (pre_cat != HOLE && winner[mouse][pre_cat][1] == 0) { // 猫无法移动到洞中
                        pre_states.emplace_back(mouse, pre_cat);
                    }
                }
            } else { // 当前轮到猫移动
                for (int pre_mouse : g[mouse]) { // 上一轮鼠的位置
                    if (winner[pre_mouse][cat][0] == 0) {
                        pre_states.emplace_back(pre_mouse, cat);
                    }
                }
            }
            return pre_states;
        };

        while (!q.empty()) {
            auto [mouse, cat, turn] = q.front(); q.pop();
            int win = winner[mouse][cat][turn]; // 最终谁赢了
            int pre_turn = turn ^ 1;
            for (auto [pre_mouse, pre_cat] : get_pre_states(mouse, cat, turn)) {
                // 情况一：如果上一回合鼠从 pre 移动到 cur，最终鼠赢，那么标记 pre 状态的 winner = 鼠
                // 情况二：如果上一回合猫从 pre 移动到 cur，最终猫赢，那么标记 pre 状态的 winner = 猫
                // 情况三：如果上一回合鼠从 pre 移动到 cur，最终猫赢，那么待定，直到我们发现从 pre 出发能到达的状态都是猫赢，那么标记 pre 状态的 winner = 猫
                // 情况四：如果上一回合猫从 pre 移动到 cur，最终鼠赢，那么待定，直到我们发现从 pre 出发能到达的状态都是鼠赢，那么标记 pre 状态的 winner = 鼠
                if (pre_turn == win - 1 || --deg[pre_mouse][pre_cat][pre_turn] == 0) {
                    winner[pre_mouse][pre_cat][pre_turn] = win;
                    q.emplace(pre_mouse, pre_cat, pre_turn); // 继续倒推
                }
            }
        }

        // 鼠在节点 1，猫在节点 2，当前轮到鼠移动
        return winner[1][2][0]; // 返回最终谁赢了（或者平局）
    }

};

int main() {
    cat_mouse_game913 ps;
    vector<vector<int>> graph = {{2,5},{3},{0,4,5},{1,4,5},{2,3},{0,2,3}};
    auto res = ps.catMouseGame(graph);
    std::cout << res << std::endl;
    return 0;
}
