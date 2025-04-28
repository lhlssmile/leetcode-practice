//
// Created by 24276 on 2025/4/13.
//

#include <iostream>
using namespace std;

class count_good_numbers1922 {
public:
    using ll = long long ;
    int countGoodNumbers(long long n) {
        ll mod = 1e9 + 7;
        ll even_count = (n + 1) / 2,odd_count = n / 2;
        auto pow_mod = [&](ll base,ll exp) {
            ll result = 1;
            base %= mod;
            while (exp > 0) {
                if (exp & 1) {
                    result = (result * base) % mod;
                }
                base = (base * base) % mod;
                exp >>= 1;
            }
            return result;
        };
        return (pow_mod(5,even_count) * pow_mod(4,odd_count)) % mod;
    }
};

int main() {
    count_good_numbers1922 sol;
    cout << sol.countGoodNumbers(4);
    return 0;
}
