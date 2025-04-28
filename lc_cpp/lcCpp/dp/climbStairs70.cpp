#include <iostream>
using namespace std;
class climb_stairs70 {
public:
    int f[46];
    int climbStairs(int n) {
        f[0] = 1,f[1] = 1;
        for(int i = 2; i <= n; ++i) {
            f[i] = f[i - 1] + f[i - 2];
        }
        return f[n];
    }
};

int main() {
    climb_stairs70 ps;
    cout << ps.climbStairs(3) << endl;
    return 0;
}
