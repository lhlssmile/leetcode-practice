#include <iostream>

class validPalindromeSolution{
public:
    bool validPalindrome(std::string s){
        size_t n = s.size();
        int left = 0,right = n - 1;
        while (left < right){
            if(s[left] != s[right]){
                return isPalindrome(s,left + 1,right) || isPalindrome(s,left,right - 1);
            }
            ++left,--right;
        }
        return true;
    }
    bool isPalindrome(const std::string s,int left,int right){
        while (left < right) {
            if(s[left] != s[right]) return false;
            ++left,--right;
        }
        return true;
    }
};
int main() {
    std::string s = "cbbcc";
    validPalindromeSolution ps;
    std::cout << ps.validPalindrome(s) << std::endl;
    return 0;
}
