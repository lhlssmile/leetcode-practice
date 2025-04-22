#include <iostream>
#include <string>
using namespace std;
class score_of_string3110 {
public:
    int scoreOfString(string s) {
        int ans = 0;
        auto n = s.size();
        for(int i = 0;i < n - 1;++i) {
            auto curr = s[i] - 'a';
            auto nxt = s[i + 1] - 'a';
            ans += abs(curr - nxt);
        }
        return ans;
    }
};

int main() {
    score_of_string3110 ps;
    string s = "zaz";
    std::cout << ps.scoreOfString(s) << std::endl;
    return 0;
}
