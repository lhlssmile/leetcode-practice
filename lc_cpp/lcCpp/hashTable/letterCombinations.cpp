#include <unordered_set>
#include <iostream>
#include <vector>
using namespace std;
class letterCombinationsSolution{
public:
    string MAPPING[10] = {"", "", "abc", "def", "ghi",
                          "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> letterCombinations(string digits) {
        int n = digits.size();
        if(n == 0) return {};
        vector<string> res;
        string path(n,0);
        dfsa(digits,0,path,res);
        return res;
    }



    vector<string> letterCombinationsA(string digits) {
        int n = digits.length();
        if (n == 0) {
            return {};
        }
        vector<string> ans;
        string path(n, 0); // 注意 path 长度一开始就是 n，不是空串
        auto dfs = [&](this auto&& dfs, int i) {
            if (i == n) {
                ans.emplace_back(path);
                return;
            }
            for (char c : MAPPING[digits[i] - '0']) {
                path[i] = c; // 直接覆盖
                dfs(i + 1);
            }
        };
        dfs(0);
        return ans;
    }
private:
    void dfsa(string& digits,int start,string& path,vector<string>& res){
        if(start == digits.size()){
            res.push_back(path);return;
        }
        for(char c : MAPPING[digits[start] - '0']){
            path[start] = c;
            dfsa(digits,start + 1,path,res);
        }
    }



};
int main() {
    letterCombinationsSolution ps;
    string digits = "23";
    auto res = ps.letterCombinations(digits);

    for (const auto& s : res) {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}
