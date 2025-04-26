#include <bits/stdc++.h>
#include <vector>
using namespace std;

class jump45{
public:
    int jump(vector<int>& nums){
        int n = nums.size();
        int end = 0;  // 当前能到达的最远位置
        int maxPos = 0;  // 下一步能到达的最远位置
        int step = 0;  // 跳跃次数
        // 当i = n-1时，我们已经到达了最后一个位置，不需要再跳跃了
        // 如果i < n，那么当i = n-1时，会执行一次不必要的跳跃
        // 例如对于nums = [2,3,1,1,4]，当i = 4时，我们已经到达终点，不需要再跳跃
        for(int i = 0; i < n - 1; i++){
            maxPos = max(maxPos, i + nums[i]);
            if(i == end){  // 到达当前能到达的最远位置
                end = maxPos;  // 更新最远位置
                step++;  // 增加跳跃次数
            }
        }
        return step;
    }
};


int main(){
    jump45 sol;
    vector<int> nums = {2,3,1,1,4};
    cout << sol.jump(nums);
}