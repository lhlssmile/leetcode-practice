#include <iostream>
#include <sstream>
#include <string>
#include <numeric> // std::gcd
int Fgcd(int a,int b){
    return b == 0 ? a : Fgcd(b,a % b);
}
class fractionAdditionSolution{
public:
    std::string fractionAddition(std::string expression) {
        long long x = 0, y = 1; // 分子，分母
        int index = 0, n = static_cast<int>(expression.size());
        while (index < n) {
            // 读取分子
            long long x1 = 0, sign = 1;
            if (expression[index] == '-' || expression[index] == '+') {
                sign = expression[index] == '-' ? -1 : 1;
                index++;
            }
            while (index < n && isdigit(expression[index])) {
                x1 = x1 * 10 + expression[index] - '0';
                index++;
            }
            x1 = sign * x1;
            index++;

            // 读取分母
            long long y1 = 0;
            while (index < n && isdigit(expression[index])) {
                y1 = y1 * 10 + expression[index] - '0';
                index++;
            }

            x = x * y1 + x1 * y;
            y *= y1;
        }
        if (x == 0) {
            return "0/1";
        }
        long long g = std::gcd(abs(x), y); // 获取最大公约数
        return std::to_string(x / g) + "/" + std::to_string(y / g);
    }
};

int main() {
    fractionAdditionSolution ps;
    std::cout << ps.fractionAddition("-12/5+1/2") << std::endl;
    return 0;
}
