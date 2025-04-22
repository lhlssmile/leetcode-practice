#include <iostream>

class numberOfStepsSolution {
public:
    numberOfStepsSolution() = default;
    ~numberOfStepsSolution() = default;
    int f[100000];
    int numberOfSteps(int num){
        f[1] = 1,f[2] = 2;
        for(int i = 3;i <= num;++i){
            if(i % 2 == 1){
                f[i] = f[i - 1] + 1;
            }else{
                f[i] = 1 + f[i / 2];
            }
        }
        return f[num];
    }
private:
    
};
int main() {
    numberOfStepsSolution ps;
    std::cout << ps.numberOfSteps(14) << std::endl;
    return 0;
}

