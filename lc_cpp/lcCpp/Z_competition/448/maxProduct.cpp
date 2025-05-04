

#include <string>
#define pb push_back
#define V vector
#define For(i, _) for (int i = 0, i##end = (_); i < i##end; ++i) // [0,_)
#define FOR(i, a, b) for (int i = (a), i##end = (b); i < i##end; ++i) // [a,b)
#include <iostream>
#include <vector>
using namespace std;
class MaxProduct{
public:
    int static  maxProduct(int n) {
        V<int> vec;
        for(;n;n /= 10) vec.pb(n  % 10);

        int ans = 0;

        For(i,vec.size()) FOR(j,i + 1,vec.size()) ans = max(ans,vec[i] * vec[j]);

        return ans;
    }
};

int main() {
    MaxProduct sol;

    cout << sol.maxProduct(31);
    return 0;
}
