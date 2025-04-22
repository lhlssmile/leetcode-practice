#include <iostream>
#include <vector>

class WhetherPalindromeSolution {
public:
    bool isPalindrome(int x){
        std::vector<int> numArray;
        if (x < 0) return false;
        if (x == 0) return true;
        int remainder;
        while (x != 0) {
            remainder = x % 10;
            numArray.emplace_back(remainder);
            x = x / 10;
        }
        bool res = true;
        size_t mid = numArray.size() / 2; //
        size_t compareTimes = mid;
        if (numArray.size() % 2 != 0){
            for (size_t i = 0; i <= compareTimes; ++i) {
                if (numArray[mid - i] != numArray[mid + i]){
                    res = false;
                    break;
                }
            }
        } else{
            for (size_t i = 0; i < compareTimes; ++i) {
                if (numArray[i] != numArray[numArray.size() - 1 - i]){
                    res = false;
                    break;
                }
            }
        }
        return res;
    }
    bool isPalindromeSimple(int x){
        if(x < 0 || (x % 10 == 0 && x != 0)){
            return false;
        }
        int revertedNumber = 0;
        while (x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }
        return x == revertedNumber || x == revertedNumber / 10;
    }
    bool static isPalindromeTwoPointer(int x){
        if(x < 0 || (x % 10 == 0 && x != 0)){
            return false;
        }
        std::vector<int> numBitArray;
        int remainder;
        while (x != 0) {
            remainder = x % 10;
            numBitArray.emplace_back(remainder);
            x = x / 10;
        }
        bool res = true;
        size_t left = 0, right = numBitArray.size() - 1;
        while (left < right){
            if (numBitArray[left] != numBitArray[right]){
                res = false;
            }
            ++left,--right;
        }
        return res;
    }
};
int main() {
    WhetherPalindromeSolution p;
    std::cout << p.isPalindromeTwoPointer(10101) << std::endl;
    return 0;
}
