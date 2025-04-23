#include <vector>
#include <iostream>

using namespace std;

class digitDP{
public:
    int countLargestGroup(int n){
        vector<int> digits;     //存放拆解的数字
        vector<vector<vector<int>>> dp; //三维记忆化
        int m;      //数字的位数
        bool leading_zero;

        void init(int n,int max_sum,bool _leading_zero = false){
            digits.clear();
            while(n){
                digits.push_back(n%10);     //拆成各个位
                n /= 10;
            }
            reverse(digits.begin(),digits.end());   //变从高位到低位
            m = digits.size();
            leading_zero = _leading_zero;
            dp.assign(m,vector<vector<int>>(max_sum + 1,vector<int>(2,-1)));
            //dp[i][sum][tight] ->i:第几位 sum：当前为止状态 ex:数位和 tight：是否有上界
        }
        int dfs(int i,int sum,bool tight){
            if(i == m){
                return (valid(sum)) ? 1 : 0;
            }
            if(dp[i][sum][tight] != -1){
                return dp[i][sum][tight];
            }
            int hi = tight ? digits[i] : 9;
            int res = 0;
            for (int d = 0; d <= hi;++d){
                res += dfs(i + 1,update(sum,d),tight && (d == hi));
            }
            return dp[i][sum][tight] = res;
        }
        bool valid(int sum){
            return sum == target;
        }
        int update(int sum,int digit){
            return sum + digit;
        }
        int count(int n,int max_sum,int _target){
            target = _target;
            init(n,max_sum);
            return dfs(0,0,true);
        }
    }
    private:
        int target;
};

int main(){
    countLargestGroup1399 cls;
    cout << cls.countLargestGroup(13) << endl;
    return 0;
}