#include <vector>
#include <stack>
using namespace std;
class Solution {
    public:
        vector<int> finalPrices(vector<int>& prices) {
            stack<int> st;
    
            vector<int> ans = prices;
    
            for (int i = 0;i < prices.size();i++) {
                while (!st.empty() && prices[i] <= prices[st.top()]) {
                    int prev = st.top();
                    st.pop();
                    ans[prev] -= prices[i];
                }
                st.push(i);
            }
            return ans;
        }
    };