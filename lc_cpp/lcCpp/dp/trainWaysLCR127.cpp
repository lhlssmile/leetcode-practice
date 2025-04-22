#include <iostream>
class trainWaysSolution{
    int f[101];
#define mod 1000000007
public:
    int trainWays(int num){
        f[0] = f[1] = 1;
        for(int i = 2;i <= num;++i){
            f[i] = (f[i - 1] + f[i - 2]) % mod;
        }
        return f[num];
    }
    int trainWaysSnConst(int num){
        //S(n) = const;
        int f0 = 1,f1 = 1;
        for(int i = 2; i <= num;++i){
            int newF = f0 + f1;
            f0 = f1;
            f1 = newF;
        }
        return f1;
    }
};
int main() {
    trainWaysSolution ps;
    std::cout << ps.trainWaysSnConst(3) << std::endl;
    return 0;
}
