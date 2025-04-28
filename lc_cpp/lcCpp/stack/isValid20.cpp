#include <unordered_map>
#include <iostream>
#include <stack>
#include <string>
using namespace std;
class is_valid20 {
    /**
    * 为什么不用左括号做键？
    因为代码的逻辑是：遇到右括号时，需要检查栈顶的左括号是否匹配。
    用右括号做键，可以直接通过 mp[c] 找到对应的左括号，然后和栈顶比较。
     */
    unordered_map<char,char> mp = {{')', '('}, {']', '['}, {'}', '{'}};
public:
    bool isValid(string s) {
        if(s.length() % 2)  return false;
        stack<char> st;
        for(char c  : s) {
            if(!mp.contains(c)) {
                st.push(c);     //此时匹配到左括号了
            }else {
                if(st.empty() || st.top() != mp[c]) {
                    return false;       //栈空了或者是不匹配左括号 false
                }
                st.pop();
            }
        }
        return st.empty();
    }
};

int main() {
    is_valid20 ps;
    cout << ps.isValid("([])") << endl;
    return 0;
}
