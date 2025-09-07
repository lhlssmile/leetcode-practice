#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

#define V vector

class Solution {
    using usi = unordered_map<string, int>;
public:
    V<int> findSubstring(string s, V<string>& words) {
        int n = words.size(), m = s.size();
        int k = words[0].size();
        int totalLen = n * k;
        V<int> ans;
        if (m < totalLen) return ans;

        // 需求表
        usi need;
        for (auto &w : words) need[w]++;

        // 遍历起点：对齐方式
        for (int offset = 0; offset < k; offset++) {
            int left = offset;
            usi window;
            int count = 0; // 窗口内匹配的单词数

            // 枚举 [offset, m-k] 每个单词起点
            for (int right = offset; right + k <= m; right += k) {
                string w = s.substr(right, k);

                // 窗口右扩
                if (need.count(w)) {
                    window[w]++;
                    count++;

                    // 如果某个单词超频，收缩窗口
                    while (window[w] > need[w]) {
                        string lw = s.substr(left, k);
                        window[lw]--;
                        left += k;
                        count--;
                    }

                    // 如果窗口刚好包含 n 个单词
                    if (count == n) {
                        ans.push_back(left);
                        // 再往前收缩一步，准备找下一个
                        string lw = s.substr(left, k);
                        window[lw]--;
                        left += k;
                        count--;
                    }
                } else {
                    // 不在 need 中，清空窗口
                    window.clear();
                    count = 0;
                    left = right + k;
                }
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    string s = "barfoothefoobarman";
    vector<string> words = {"foo", "bar"};
    
    vector<int> result = sol.findSubstring(s, words);
    
    cout << "Result: ";
    for (int pos : result) {
        cout << pos << " ";
    }
    cout << endl;
    
    return 0;
}