//
// Created by 24276 on 2025/3/28.
//

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class  exist79 {
public:
    /**
     * 一个一个字母匹配 中途只要有一个symbol(上下左右不匹配直接返回错)
     * @param board
     * @param word
     * @return
     */
public:
    static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        // 从每个格子作为起点尝试
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool exist1(vector<vector<char>>& board, string word) {
        pmr::unordered_map<char, int> cnt;
        for (auto& row : board) {
            for (char c : row) {
                cnt[c]++;
            }
        }

        // 优化一
        unordered_map<char, int> word_cnt;
        for (char c : word) {
            if (++word_cnt[c] > cnt[c]) {
                return false;
            }
        }

        // 优化二
        if (cnt[word.back()] < cnt[word[0]]) {
            ranges::reverse(word);
        }

        int m = board.size(), n = board[0].size();
        auto dfs = [&](auto&& dfs, int i, int j, int k) -> bool {
            if (board[i][j] != word[k]) { // 匹配失败
                return false;
            }
            if (k + 1 == word.length()) { // 匹配成功！
                return true;
            }
            board[i][j] = 0; // 标记访问过
            for (auto& [dx, dy] : DIRS) {
                int x = i + dx, y = j + dy; // 相邻格子
                if (0 <= x && x < m && 0 <= y && y < n && dfs(dfs,x, y, k + 1)) {
                    return true; // 搜到了！
                }
            }
            board[i][j] = word[k]; // 恢复现场
            return false; // 没搜到
        };
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(dfs,i, j, 0)) {
                    return true; // 搜到了！
                }
            }
        }
        return false; // 没搜到
    }

private:
    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int pos) {
        // 匹配完成
        if (pos == word.size()) return true;

        // 越界或当前字符不匹配
        int m = board.size(), n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[pos]) {
            return false;
        }

        // 标记当前格子为已访问
        char temp = board[i][j];
        board[i][j] = '#';

        // 向四个方向递归
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // 右、下、左、上
        for (auto& dir : directions) {
            int ni = i + dir[0];
            int nj = j + dir[1];
            if (dfs(board, word, ni, nj, pos + 1)) {
                return true;
            }
        }

        // 回溯：恢复格子
        board[i][j] = temp;
        return false;
    }
};

int main() {
    exist79 solution;
    vector<vector<char>> board = {{'A','B','C','E'},
                                     {'S','F','C','S'},
                                     {'A','D','E','E'}};
    string word = "SEE";
    bool result = solution.exist1(board, word);
    cout << (result ? "true" : "false") << endl; // 输出 true
    return 0;
}
