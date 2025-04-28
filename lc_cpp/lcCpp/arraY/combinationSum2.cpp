#include <vector>
#include <iostream>
#include <algorithm>

class CombinationSum2Solution {
public:
    std::vector<std::vector<int>> combinationSums(std::vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> res;
        std::vector<int> path;
        backTrack(candidates, target, 0, path, res);
        return res;
    }

private:
    void backTrack(std::vector<int>& candidates, int target, int start,
                   std::vector<int>& path, std::vector<std::vector<int>>& res) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        for (int i = start; i < candidates.size(); ++i) {
            if (i > start && candidates[i] == candidates[i - 1]) continue;
            if (candidates[i] > target) break;
            path.push_back(candidates[i]);
            backTrack(candidates, target - candidates[i], i + 1, path, res);
            path.pop_back();
        }
    }
};

int main() {
    CombinationSum2Solution solution;
    std::vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    std::vector<std::vector<int>> result = solution.combinationSums(candidates, target);

    // 打印结果
    std::cout << "[" << std::endl;
    for (const auto& combination : result) {
        std::cout << "  [";
        for (int i = 0; i < combination.size(); ++i) {
            std::cout << combination[i];
            if (i != combination.size() - 1) std::cout << ",";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "]" << std::endl;

    return 0;
}
