#include <string>
#include <iostream>
using namespace std;
class break_palindrome1328 {
public:
    string breakPalindrome(string palindrome) {
        int n = palindrome.size();
        if(n <= 1) return "";
        int left = 0,right = n - 1;
        while(left < right) {
            if(palindrome[left] - 'a' != 0 && palindrome[left] == palindrome[right]) {
                palindrome[left] = 'a';
                break;
            }
            ++left,--right;
        }
        if(left >= right) {
            palindrome[n - 1] = 'b';
        }
        return palindrome;
    }
    string inteligentWay(string palindrome) {
        int n = palindrome.size();
        if(n <= 1) return "";
        for(int i = 0;i < n / 2;++i) {
            if(palindrome[i] != 'a') {
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        palindrome[n - 1] = 'b';
        return palindrome;
    }
};

int main() {
    break_palindrome1328 ps;
    cout << ps.breakPalindrome("aba") << endl;
    return 0;
}
