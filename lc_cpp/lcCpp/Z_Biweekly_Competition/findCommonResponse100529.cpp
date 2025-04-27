#include <vector>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/**
 * 给你一个二维字符串数组 responses，其中每个 responses[i] 是一个字符串数组，表示第 i 天调查的回答结果。

请返回在对每个 responses[i] 中的回答 去重 后，所有天数中 最常见 的回答。如果有多个回答出现频率相同，则返回 字典序最小 的那个回答。

一个字符串 a 在字典序上 小于 另一个字符串 b 的条件是：在第一个不相同的位置上，a 中的字母比 b 中对应的字母在字母表中靠前。

如果前 min(a.length, b.length) 个字符都相同，则较短的字符串字典序更小。

 

示例 1：

输入： responses = [["good","ok","good","ok"],["ok","bad","good","ok","ok"],["good"],["bad"]]

输出： "good"

解释：

每个列表去重后，得到 responses = [["good", "ok"], ["ok", "bad", "good"], ["good"], ["bad"]]。
"good" 出现了 3 次，"ok" 出现了 2 次，"bad" 也出现了 2 次。
返回 "good"，因为它出现的频率最高。
示例 2：

输入： responses = [["good","ok","good"],["ok","bad"],["bad","notsure"],["great","good"]]

输出： "bad"

解释：

每个列表去重后，responses = [["good", "ok"], ["ok", "bad"], ["bad", "notsure"], ["great", "good"]]。
"bad"、"good" 和 "ok" 都出现了 2 次。
返回 "bad"，因为它在这些最高频率的词中字典序最小。
 

提示：

1 <= responses.length <= 1000
1 <= responses[i].length <= 1000
1 <= responses[i][j].length <= 10
responses[i][j] 仅由小写英文字母组成
 * 解题思路：
 * 1. 遍历每个response数组，使用unordered_set去重
 * 2. 将去重后的每个字符串存入unordered_map统计出现次数
 * 3. 遍历map找到出现次数最多的字符串，如果有多个则选择字典序最小的
 * 
 * 时间复杂度：O(n*m)，其中n是responses的长度，m是每个response的平均长度
 * 空间复杂度：O(n*m)，用于存储去重后的字符串和统计次数
 */
class findCommonResponse100529{
public:
    string findCommonResponse(vector<vector<string>>& responses){
        unordered_map<string,int> cnt;
        for(auto const& response : responses){
            unordered_set<string> st(response.begin(),response.end());
            for(auto const& s : st){
                cnt[s]++;
            }
        }
        
        string res;
        int maxCnt = 0;
        for(auto const& [s, c] : cnt){
            if(c > maxCnt || (c == maxCnt && s < res)){
                maxCnt = c;
                res = s;
            }
        }
        return res;
    }
};

int main(){
    findCommonResponse100529 sol;
    vector<vector<string>> responses = {
        {"good","ok","good"},
        {"ok", "bad"},
        {"bad","notsure"},
        {"great","good"}

    };
    sol.findCommonResponse(responses);
}