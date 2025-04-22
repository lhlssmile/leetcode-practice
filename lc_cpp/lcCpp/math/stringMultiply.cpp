#include<iostream>
#include <string>
#include <typeinfo>
#include <vector>
class stringMultiplySolution{
public:
    std::string stringMultiply(std::string num1,std::string num2){
        int n1_length = static_cast<int>(num1.size());
        int n2_length = static_cast<int>(num2.size());
        if(num1 == "0" || num2 == "0") return "0";
        std::vector<int> result(n1_length + n2_length,0);
        for(int i = n1_length - 1;i >= 0; --i){
            for(int j = n2_length - 1;j >= 0; --j){
                //calculate standard and carry bit
                int current = (num1[i] - '0') * (num2[j] - '0');
                int sum = current + result[i + j + 1];
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }
        std::string result_str;
        for(const auto& x : result){
            if(!(result_str.empty() && x == 0)){
                result_str += std::to_string(x);
            }
        }
        return result_str;
    }

};
int main() {
    stringMultiplySolution s;
    std::cout << s.stringMultiply("13","22") << std::endl;
    return 0;
}
