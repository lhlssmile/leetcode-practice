#include <vector>
#include <iostream>
class arraySignSolution{
public:
    int arraySign(std::vector<int>& nums){
        int sign = 1;
        for(const auto x : nums){
            if(x == 0) return 0;
            if(x < 0){
                sign *= -1;
            }
        }
        return sign;
    }
};
int main() {
    arraySignSolution ps;
    std::vector<int > nums = {-1,-2,-3,-4,3,2,-1};
    std::cout << ps.arraySign(nums) << std::endl;
    return 0;
}
