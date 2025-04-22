//
// Created by 24276 on 2025/4/13.
//


#include <iostream>
using namespace std;
class find_closest100633 {
public:
    const int x_arr = 1;
    const int y_arr = 2;
    const int xy_arr = 0;
    int findClosest(int x,int y,int z) {
        if (abs(x - z) == abs(y - z)) return xy_arr;
        return abs(x - z) > abs(y - z) ? y_arr : x_arr;
    }
};

int main() {
    find_closest100633 sol;
    cout << sol.findClosest(1,5,3);
    return 0;
}
