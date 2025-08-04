//
// Created by 24276 on 2025/8/4.
//

#include <vector>
#include <string>
using namespace std;
class count_texts {
public:
    int countTexts (string pressedKeys) {
        int MOD = 1e9 + 7;
        int n = pressedKeys.size();
        vector<int> dp(n + 1, 0);
        dp[n] = 1;

        for (int i = n - 1; i >= 0;i--) {
            int limit = (pressedKeys[i] == '7' || pressedKeys[i] == '9') ? 4 : 3;
            for (int k = 1; k <= limit && i + k <= n;k++)  {
                bool ok = true;
                for (int j = i; j < i + k;j++) {
                    if (pressedKeys[i] != pressedKeys[j]) {
                        ok =false;
                        break;
                    }
                }
                if (!ok) break;
                dp[i] = (dp[i] + dp[i + k]) % MOD;
            }
        }
        return dp[0];
    }
};

int main() {
    return 0;
}
