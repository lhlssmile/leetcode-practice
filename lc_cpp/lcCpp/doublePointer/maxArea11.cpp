#include <vector>
#include <iostream>
using namespace std;
class max_area11 {
public:
    int maxArea(vector<int>& height) {
        int ans = 0;
        int left = 0,right = height.size() - 1;
        while(left < right) {
            //乘前后缀数组?  小的加 不要都加
            int chooseHeight = 0;
            if(height[left] < height[right]) {
                chooseHeight = height[left];
            }else {
                chooseHeight = height[right];
            }
            int current_area = (right - left) * chooseHeight;
            chooseHeight == height[left] ? left++ : right--;
            ans = max(ans,current_area);
        }
        return ans;
    }
    int maxAreaDOUBLEP(vector<int>& height) {
        int l = 0,r = height.size() - 1;
        int ans = 0;
        while(l < r) {
            int area = min(height[l],height[r]) * (r - l);
            ans = max(ans,area);
            if(height[l] < height[r]) {
                ++l;
            }else {
                --r;
            }
        }
        return ans;
    }
};

int main() {
    max_area11 solution;
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    cout << solution.maxArea(height) << endl;
    return 0;
}

