//
// Created by 24276 on 2025/4/15.
//
#include <iostream>
using namespace std;
class max_container3492 {
public:
    int maxContainers(int n, int w, int maxWeight) {
        return min(maxWeight / w ,n * n);
    }
};

int main() {
    max_container3492 sol;
    cout << sol.maxContainers(2,3,15);
    return 0;
}
