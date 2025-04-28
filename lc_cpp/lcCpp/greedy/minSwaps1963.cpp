#include <string>
#include <iostream>
using namespace std;
class min_swaps1963 {
public:
    int minSwaps(string s) {
        //不用真的交换    [ + 1, ] - 1;
        int ans = 0, c = 0;
        for(char b : s) {
            if(b == '[') {
                c++;
            }else if(c > 0){
                c--;
            }else {
                //此时为右括号 直接改成左括号[
                ans++;
                c++;
            }
        }
        return ans;
    }
};

int main() {
    min_swaps1963 ps;
    string s = "]]][[[";    // [] ][[[
    ps.minSwaps(s);
    return 0;
}
