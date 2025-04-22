#include <vector>
#include <iostream>
using namespace std;
class even_odd_bit2595 {
public:
    static vector<int> evenOddBit(int n) {
        vector<int> ans(2);
        for(int i = 0;n;n >>= 1) {
            ans[i] += n & 1;
            i ^= 1;
        }
        return ans;
    }
};

int main() {
    even_odd_bit2595 ps;
    int n = 50;
    auto res = ps.evenOddBit(n);
    cout << "[" << "";
    for(auto const& bit : res) {
        cout << bit << " ";
    }
    cout << "]" << endl;
    std::cin.get();
    return 0;
}
