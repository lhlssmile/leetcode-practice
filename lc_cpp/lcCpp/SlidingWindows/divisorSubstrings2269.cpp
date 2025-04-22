#include <string>
#include <iostream>
using namespace std;
class divisor_substrings2269 {
public:
    int divisorSubstrings(int num,int k) {
        auto s = std::to_string(num);
        auto n = s.size();
        int ans = 0;
        for(int i = k;i <= n; ++i) {
            auto x = stoi(s.substr(i - k,k));
            if(x > 0 && num % x == 0) {
                ans++;
            }
        }
        return ans;
    }
    //math
    int divisorSubstring(int num,int k) {
        long long m = pow(10, k);
        int ans = 0;
        //只要n >= m /10一直循环
        for (int n = num; n >= m / 10; n /= 10) {
            int x = n % m;
            if (x > 0 && num % x == 0) {
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    divisor_substrings2269 ps;
    cout << ps.divisorSubstring(240,2) << endl;
    return 0;
}
