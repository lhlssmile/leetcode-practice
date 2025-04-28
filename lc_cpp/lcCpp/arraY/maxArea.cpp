#include <iostream>
#include <vector>
using namespace std;
class maxAreaSolution{
public:
    int maxArea(vector<int>& height){
        int left = 0,right = height.size() - 1;
        int maxArea  = 0;
        while(left < right){
            int area = (right - left) * std::min(height[left],height[right]);
            maxArea = std::max(area,maxArea);
            height[left] < height[right] ? ++left : --right;
        }
        return maxArea;
    }
};
int main() {
    maxAreaSolution ps;
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    int res = ps.maxArea(height);
    cout << res << endl;
    return 0;
}
