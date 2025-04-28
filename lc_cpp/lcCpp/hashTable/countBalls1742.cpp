#include <iostream>
#include <unordered_map>
#include <array>
const int MX = 100'001;
//二维数组s
std::array<int,46> s[MX];
class count_balls1742 {
public:
    //map 不用存储球的各个id 直接计数就行
    std::unordered_map<int,int> map;
    //暴力枚举
    int countBalls1(int lowLimit,int highLimit) {
        int maxBalls = 0;   //max ball counts
        for(int ball = lowLimit;ball <= highLimit;++ball) {
            int boxId = 0;
            int temp = ball;
            while(temp > 0) {
                boxId += temp % 10;
                temp /= 10;
            }
            map[boxId]++;
            maxBalls = std::max(maxBalls,map[boxId]);
        }
        return maxBalls;
    }
    //预处理前缀和
    int countBalls(int lowLimit, int highLimit) {
        int ans = 0;
        for (int j = 1; j < s[0].size(); j++) {
            ans = std::max(ans, s[highLimit][j] - s[lowLimit - 1][j]);
        }
        return ans;
    }



};
auto init = [] {
    for (int i = 1; i < MX; i++) {
        s[i] = s[i - 1];
        int sum = 0;
        for (int x = i; x > 0; x /= 10) {
            sum += x % 10;
        }
        s[i][sum]++;
    }
    return 0;
}();

int main() {
    count_balls1742 ps;
    std::cout << ps.countBalls(1,10) << std::endl;;
    return 0;
}

