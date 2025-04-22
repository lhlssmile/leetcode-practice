#include<iostream>
#include<math.h>
class bulbSwitchSolution{
public:
    int bulbSwitch(int n){
        // init n nums of bulb
        return static_cast<int>(std::sqrt(n));
    }
};
int main() {
    bulbSwitchSolution ps;
    std::cout << ps.bulbSwitch(4) << std::endl;
    return 0;
}
