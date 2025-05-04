//
// Created by 24276 on 2025/5/4.
//

#include "../template/mylib.h"

#include <vector>

class num_equiv_domino_pairs1128 {
public:
    int static numEquivDominoPairs(V<V<int>>& dominoes) {
        int ans = 0;
        int cnt[10][10]{};

        for(auto& d : dominoes) {
            auto [a,b] = minmax(d[0],d[1]);
            ans += cnt[a][b]++;
        }
        return ans;
    }
};

int main() {
    num_equiv_domino_pairs1128 sol;
    vector<vector<int>> dominoes = {
        {1,2},{2,1},{3,4},{5,6}
    };
    dominoes = {
        {1, 2}, {2, 1}, {3, 4}
    };
    cout << sol.numEquivDominoPairs(dominoes);
    return 0;
}
