#include <vector>
#include <iostream>
using namespace std;
class trap42 {
public:
    int trap(vector<int>& height) {
        auto n = height.size();
        vector<int> pre_max(n);
        pre_max[0] = height[0];
        for(int i = 1;i < n;++i) {
            pre_max[i] = max(pre_max[i - 1],height[i]);
        }
        vector<int> suf_max(n);
        suf_max[n - 1] = height[n - 1];
        for(int i = n -2;i >= 0;--i) {
            suf_max[i] = max(suf_max[i + 1],height[i]);
        }
        int ans = 0;
        for(int i = 0;i < n;++i) {
            ans += min(pre_max[i],suf_max[i] )- height[i];
        }
        return ans;
    }
    int trapUseDoublePointer(vector<int>& height) {
        auto n = height.size();
        int left = 0,right = n - 1;
        int ans = 0,pre_max = 0,suf_max = 0;
        while(left < right) {
            pre_max = max(pre_max,height[left]);
            suf_max = max(suf_max,height[right]);
            ans += pre_max < suf_max ? pre_max - height[left++] : suf_max - height[right--];
        }
        return ans;
    }
};

int main() {
    trap42 solution;
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << solution.trapUseDoublePointer(height) << endl;
    return 0;
}
