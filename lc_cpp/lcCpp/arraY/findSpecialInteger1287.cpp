#include <vector>
#include <iostream>
#include <ranges>

#include <algorithm>
using namespace std;
class find_special_integer_1287{
public:
    static int findSpecialInteger(vector<int>& arr) {
        int appearTimes = (arr.size() / 4) + 1;
        if(arr.size() == 1) return arr[0];
        int slow = 0;
        int ans = 0;
        for(int fast = slow + 1;fast < arr.size();) {
            if(arr[slow] != arr[fast]) {
                slow = fast;
                appearTimes = arr.size() / 4;
            }else {
                ++fast;
                --appearTimes;
            }
            if(appearTimes < 0) {
                ans = arr[slow];
                break;
            }
        }
        return ans;
    }
    static int findSpecInteger(vector<int>& nums) {
        int appearTimes = (nums.size() / 4) + 1;
        int slow = 0;
        for(int fast = 1;fast < nums.size();++fast) {
            if(nums[slow] == nums[fast]) {
                if(fast - slow + 1 >= appearTimes) {
                    return nums[slow];
                }
            }else {
                slow = fast;
            }
        }
        return nums[slow];
    }

    int findSpecialIntege1r(vector<int>& arr) {
        int m = arr.size() / 4;
        for (int i : {m, m * 2 + 1}) {
            int x = arr[i];
            // 包含 algorithm 头文件
            int j = std::lower_bound(arr.begin(), arr.end(), x) - arr.begin();
            if (arr[j + m] == x) {
                return x;
            }
        }
        return arr[m * 3 + 2];
    }

};
int main(){
    find_special_integer_1287 ps;
    vector<int> arr = {1,1,1,1,1,1,2,3,4,5,6,7,8,9,10,11,12,12,12,12};
    auto ans = ps.findSpecialIntege1r(arr);
    cout << ans << endl;
}