#include <iostream>
class numberOfStepsSolution{
public:
    int steps = 0;
    int numberOfSteps(int num){
        if(num == 0) return 0;
        if(num % 2 == 0){
            ++steps;
            numberOfSteps(num / 2);
        }else{
            ++steps;
            numberOfSteps(num - 1);
        }

        return steps;
    }
    int numbersOfSteps(int num){
        int ret = 0;
        while(num){
            // num > 1? 则需要一个除二的操作，           看最低一位是否为1 即判断是否是奇数 奇数则+1
            ret += (num > 1 ? 1 : 0) + (num & 0x01);
            //右移一位 相当于除二向下取余
            num >>= 1;
        }
        return ret;
    }
};
int main() {
    numberOfStepsSolution ps;
    std::cout << ps.numbersOfSteps(14) << std::endl;
    return 0;
}
