//
// Created by 24276 on 2025/4/3.
//

#include  <vector>
#include <iostream>
using namespace std;

class partition_labels763 {
public:
    vector<int> partitionLabels(string s) {
        vector<int> la(26,0);
        for(int i = 0;i < s.size();i++) {
            la[s[i] - 'a'] = i;
        }
        vector<int> ans;
        int start = 0;  //当前子字符串的起始 位置
        int max_end;    //当前子字符串的最远结束位置
        for(int i = 0;i < s.size();i++) {
            //每遍历一个字符 计入最大截止下标 若出现下一个大于当前的 即可截取一个子字符串
            max_end = max(max_end,la[s[i] - 'a']);
            if(i == max_end) {
                ans.push_back(i - start + 1);
                start = i + 1;
            }
        }
        return ans;
    }
};

int main() {
    partition_labels763 solution;
    string s = "ababcbacadefegdehijhklij";
    auto res = solution.partitionLabels(s);
    for (int subScript : res) {
        cout << subScript << " ";
    }
    return 0;
}
