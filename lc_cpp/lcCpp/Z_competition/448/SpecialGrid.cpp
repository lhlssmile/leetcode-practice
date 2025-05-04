//
// Created by 24276 on 2025/5/4.
//

#define V vector
#include <vector>
using namespace std;

class special_grid {
public:
    V<V<int>> specialGrid(int n) {
        if(n == 0) return {{0}};
        V a(1 << n,V<int>(1 << n));
        int val = 0;

        auto dfs = [&](this auto&& dfs,int u,int d,int l ,int r) ->void {
            if (d - u == 1) {
                a[u][l] = val++;
                return ;
            }
            int m = (d - u) / 2;
            dfs(u,u + m,l + m,r);
            dfs(u + m,d,l + m,r);
            dfs(u + m,d,l,l + m);
            dfs(u,u + m,l,l + m);

        };
        dfs(0,1 << n,0,1 << n);
        return a;
    }
};

int main() {
    special_grid sol;
    sol.specialGrid(1);
    return 0;
}
