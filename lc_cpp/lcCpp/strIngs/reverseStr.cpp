#include <iostream>
class reverseStrSolution{
public:
    std::string reverseStr(std::string s,int k){
        if(k == 1) return s;
        int n = s.size();
        for (int i = 0; i < n; i+= 2*k) {
            int end = std::min(i + k,n);
            std::reverse(s.begin() + i,s.begin() + end);
        }
        return s;
    }
};
int main() {
    reverseStrSolution ps;
    std::cout << ps.reverseStr("abcdefghijklmn",2) << std::endl;
    return 0;
}
