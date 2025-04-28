#include <vector>
#include <iostream>
using namespace std;
class max_profit121 {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0,minimum_purchase = prices[0];
        auto n = prices.size();
        for(int i = 1; i < n;++i) {
            minimum_purchase = std::min(minimum_purchase,prices[i]);
            max_profit = std::max(max_profit,prices[i] - minimum_purchase);
        }
        return max_profit;
    }
    int maxProfita(vector<int>& prices) {
        int profit = 0;
        int buy = INT_MAX;
        for(int i = 0; i < prices.size();++i) {
            if(prices[i] < buy) buy = prices[i];
            int profit_now = prices[i] - buy;
            if(profit_now > profit) profit = profit_now;
        }
        return profit;
    }
};

int main() {
    max_profit121 ps;
    vector<int> prices = {7,1,5,3,6,4};
    cout << ps.maxProfit(prices) << endl;
    return 0;
}
