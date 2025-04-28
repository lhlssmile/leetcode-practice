#include <vector>
using namespace std;
#include <iostream>
class diagonal_prime2614 {
public:
    int diagonalPrime(vector<vector<int>>& nums) {
        int ans = 0;auto n = nums.size();
        for(int i = 0;i < n;i++) {
            for(int x : {nums[i][i],nums[i][n - i - 1]}) {
                if(isPrime(x) && x > ans) {
                    ans = x;
                }
            }
        }
        return ans;
    }
private:
    bool isPrime(int x) {
        for(int i = 2;i * i <= x;++i) {
            if(x % i == 0) {
                return false;
            }
        }
        return x >= 2;
    }
};

int main() {
    diagonal_prime2614 ps;
    vector<vector<int>> nums = {{1,2,3},{5,6,7},{9,10,11}};
    cout << ps.diagonalPrime(nums) << endl;
    return 0;
}
