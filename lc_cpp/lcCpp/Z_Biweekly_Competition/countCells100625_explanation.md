# 统计满足条件的单元格数量 - 题解

## 问题描述
给定一个由字符组成的 m x n 矩阵 grid 和一个字符串 pattern，统计满足以下条件的单元格数量：
- 该单元格必须属于至少一个等于 pattern 的水平子串
- 且属于至少一个等于 pattern 的垂直子串

## 解题思路
这道题的关键在于如何高效地找到所有匹配 pattern 的水平子串和垂直子串。我们使用了KMP算法来优化字符串匹配过程。

### 1. KMP算法简介
KMP算法是一种高效的字符串匹配算法，它的核心思想是：
- 预处理模式串，生成最长前缀后缀数组(LPS)
- 在匹配过程中，利用LPS数组跳过不必要的比较

### 2. 主要函数解析

#### 2.1 computeLPS函数
```cpp
vector<int> computeLPS(string pattern) {
    int n = pattern.length();
    vector<int> lps(n, 0);
    int len = 0;
    int i = 1;
    
    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
```
这个函数用于计算模式串的LPS数组：
- `lps[i]` 表示 pattern[0..i] 的最长相等前缀后缀长度
- 时间复杂度：O(n)，其中n是pattern的长度

#### 2.2 markHorizontal函数
```cpp
void markHorizontal(vector<vector<char>>& grid, vector<vector<bool>>& hori, string pattern) {
    // 将网格转换为字符串
    string gridStr;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            gridStr += grid[i][j];
        }
    }
    
    // KMP匹配
    int i = 0, j = 0;
    while (i < gridStr.length()) {
        if (pattern[j] == gridStr[i]) {
            i++;
            j++;
        }
        
        if (j == len) {
            // 找到匹配，标记位置
            int start = i - j;
            for (int k = 0; k < len; ++k) {
                int pos = start + k;
                int row = pos / n;
                int col = pos % n;
                hori[row][col] = true;
            }
            j = lps[j - 1];
        } else if (i < gridStr.length() && pattern[j] != gridStr[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}
```
这个函数处理水平方向的匹配：
- 将整个网格按行展开成一个字符串
- 使用KMP算法找到所有匹配的位置
- 将匹配位置转换回网格坐标并标记

#### 2.3 markVertical函数
```cpp
void markVertical(vector<vector<char>>& grid, vector<vector<bool>>& vert, string pattern) {
    // 对每一列单独处理
    for (int j = 0; j < n; ++j) {
        string colStr;
        for (int i = 0; i < m; ++i) {
            colStr += grid[i][j];
        }
        
        // KMP匹配
        int i = 0, k = 0;
        while (i < colStr.length()) {
            if (pattern[k] == colStr[i]) {
                i++;
                k++;
            }
            
            if (k == len) {
                // 找到匹配，标记位置
                int start = i - k;
                for (int l = 0; l < len; ++l) {
                    vert[start + l][j] = true;
                }
                k = lps[k - 1];
            } else if (i < colStr.length() && pattern[k] != colStr[i]) {
                if (k != 0) {
                    k = lps[k - 1];
                } else {
                    i++;
                }
            }
        }
    }
}
```
这个函数处理垂直方向的匹配：
- 对每一列单独处理，将列转换为字符串
- 使用KMP算法找到匹配位置
- 标记匹配的单元格

### 3. 时间复杂度分析
- LPS数组计算：O(len)
- 水平匹配：O(m * n + len)
- 垂直匹配：O(m * n + len)
- 总体复杂度：O(m * n + len)

### 4. 空间复杂度分析
- LPS数组：O(len)
- 标记数组：O(m * n)
- 总体空间复杂度：O(m * n + len)

## 优化思路
1. 使用KMP算法替代暴力匹配，减少重复比较
2. 将网格转换为字符串处理，简化匹配逻辑
3. 分别处理水平和垂直方向，避免复杂的边界条件

## 示例
输入：
```
grid = [
    ['a', 'a', 'c', 'c'],
    ['b', 'b', 'b', 'c'],
    ['a', 'a', 'b', 'a'],
    ['c', 'a', 'a', 'c'],
    ['a', 'a', 'c', 'c']
]
pattern = "abaca"
```

处理过程：
1. 水平方向：将网格展开为 "aaccbbbcabaacaaacc"
2. 垂直方向：对每一列分别处理
3. 统计同时满足水平和垂直匹配的单元格数量

输出：1 