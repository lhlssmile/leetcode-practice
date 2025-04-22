#include <vector>
#include <iostream>
class yangHuiTriangle1Solution{
public:
    std::vector<std::vector<int>> generateRow(int numRows){
        std::vector<std::vector<int>> dp;

        // 初始化前两行
        if (numRows >= 1) {
            dp.push_back({1});
        }
        if (numRows >= 2) {
            dp.push_back({1, 1});
        }

        // 生成后续行（从第三行开始）
        for (int row = 2; row < numRows; ++row) {
            std::vector<int> newRow(row + 1, 1);  // 首尾元素都是1
            const auto& prevRow = dp[row-1];      // 获取前一行

            // 计算中间元素
            for (int col = 1; col < row; ++col) {
                newRow[col] = prevRow[col-1] + prevRow[col];
            }

            dp.push_back(newRow);
        }
        return dp;
    }
};
int main() {
    yangHuiTriangle1Solution sol;
    auto result = sol.generateRow(5);

    // 正确格式化输出
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "\n  [";
        for (size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j];
            if (j != result[i].size()-1) std::cout << ",";
        }
        std::cout << "]";
    }
    std::cout << "\n]" << std::endl;

    return 0;
}
