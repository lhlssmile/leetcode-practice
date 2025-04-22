#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class max_distance1552 {
public:
    int maxDistance(vector<int>& position,int m) {
        std::sort(position.begin(),position.end());
        int n = position.size();
        if(m > n) return  0;
        int low = 0;
        int high = position[n - 1] - position[low];
        while(low <= high) {
            int mid = low + (high - low ) / 2;
            if(canReplace(position,m,mid)) {
                low = mid + 1;
            }else {
                high = mid - 1;
            }
        }
        return high;
    }
private:
    bool canReplace(vector<int>& position,int m,int minDist){
        //看看此时的距离minDist能不能分完m个球      如果可以尝试增大 否则减小
        //默认分给第一个位置一个了
        int count = 1;
        int last_pos = position[0];
        for(int i = 1;i < position.size(); ++i){
            if(position[i] - last_pos >= minDist){
                ++count;
                //更新放的这个球的位置
                last_pos = position[i];
                //还可以放球 所以要增大距离
                if(count >= m) return true;
            }
        }
        return false;
    }
};

int main() {
    max_distance1552 ps;
    vector<int> positions = {1,2,3,4,7};
    cout << ps.maxDistance(positions,2) << endl;
    return 0;
}
