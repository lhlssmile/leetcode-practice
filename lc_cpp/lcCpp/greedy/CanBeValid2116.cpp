#include <iostream>
#include <string>
using namespace std;
class can_be_valid2116 {
public:
    /**
     * 贪心:任何情况下 右括号的数量不能超过左括号的数量    再根据locked[i]灵活修改
     * @param s str s
     * @param locked locked[i] can modify s[i]
     * @return
     */
    bool canBeValid(string s,string locked) {
        if(s.size() % 2 != 0)   return false;
        int balance = 0;    //左 - 右
        int wildCards = 0;
        auto n = s.size();
        //左到右 前缀 不要让 右括号多于左括号
        for(int i = 0;i < n;++i) {
            if(locked[i] == '0') {
                wildCards++;
            }else if(s[i] == '(') {
                balance++;
            }else {
                balance--;
            }
            if(balance + wildCards < 0) {
                return false;
            }
        }
        for(int i = n - 1;i >= 0;i--) {
            if(locked[i] == '0') {
                wildCards++;
            }else if(s[i] == ')') {
                balance++;
            }else {
                balance--;
            }
            if(balance + wildCards < 0) {
                return false;
            }
        }
        return true;
    }
    bool canBeValidA(string s,string locked) {
        auto n = s.size();
        if (n % 2 != 0) return false;
        int mn = 0,mx = 0;
        for(int i = 0;i < n;++i) {
            if(locked[i] == '1') {
                int d = s[i] == '(' ? 1 : -1;
                mx += d;
                if(mx < 0) {
                    return false;
                }
                mn += d;
            }else {
                mx++;
                mn--;
            }
            if(mn < 0) {
                mn = 1;
            }
        }
        return mn == 0;
    }
};

int main() {
    can_be_valid2116 solution;
    std::string s = "(((())(((())";
    std::string locked = "111111010111";
    bool result = solution.canBeValid(s, locked);
    std::cout << (result ? "true" : "false") << std::endl; // 输出: true
    return 0;
}
