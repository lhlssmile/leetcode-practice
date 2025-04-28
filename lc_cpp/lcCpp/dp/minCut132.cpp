#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <windows.h>
#include <psapi.h>
using namespace std;

class min_cut132 {
public:
    int minCut(string s) {
        int n = s.size();
        if (n <= 1) return 0;

        // 预计算回文
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if (len == 2) {
                    dp[i][j] = (s[i] == s[j]);
                } else {
                    dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
                }
            }
        }

        // 计算最小分割
        vector<int> cuts(n, 0);
        for (int i = 0; i < n; ++i) {
            cuts[i] = i; // 最坏情况
            if (dp[0][i]) {
                cuts[i] = 0; // 整个是回文
            } else {
                for (int j = 1; j <= i; ++j) {
                    if (dp[j][i]) {
                        cuts[i] = min(cuts[i], cuts[j-1] + 1);
                    }
                }
            }
        }
        return cuts[n-1];
    }
};

void printMemory() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    cout << "Memory: " << memInfo.WorkingSetSize / 1024 << " KB" << endl;
}

int main() {
    min_cut132 ps;
    string s = "aabcde";
    auto start = chrono::high_resolution_clock::now();
    int result = ps.minCut(s);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Result: " << result << endl;
    cout << "Time: " << duration.count() << " us" << endl;
    printMemory();
    return 0;
}