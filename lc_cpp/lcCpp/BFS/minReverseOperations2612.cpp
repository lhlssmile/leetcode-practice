#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;
class min_reverse_operations2612 {
public:
    vector<int> minReverseOperations(int n,int p,vector<int>& banned,int k) {
        unordered_set<int> banned_set{banned.begin(),banned.end()};
        set<int> indices[2];
        for(int i = 0;i < n;++i) {
            if(i != p && !banned_set.contains(i)) {
                indices[i % 2].insert(i);
            }
        }
        indices[0].insert(n);       //哨兵 无需判断   it != st.end()
        indices[1].insert(n);

        vector<int> ans(n,-1);
        ans[p] = 0;
        queue<int> q;
        q.push(p);
        while(!q.empty()) {
            int i = q.front();q.pop();
            //indices[mn % 2]中的mn 到mx的所有下表都可以从i反转到
            int mn = max(i - k + 1,k - i - 1);
            int mx = min(i + k - 1,n * 2 - k - i - 1);
            auto& st = indices[mn % 2];
            for(auto it = st.lower_bound(mn);*it <= mx;it = st.erase(it)) {
                ans[*it] = ans[i] + 1;
                q.push(*it);
            }
        }
        return ans;
    }
};

int main() {
    // 测试用例1
    min_reverse_operations2612 solution;
    int n = 4, p = 0, k = 2;
    vector<int> banned = {1, 2};
    vector<int> result = solution.minReverseOperations(n, p, banned, k);
    
    cout << "结果: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    
    // 测试用例2
    n = 5, p = 0, k = 3;
    banned = {2, 4};
    result = solution.minReverseOperations(n, p, banned, k);

    cout << "结果: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
