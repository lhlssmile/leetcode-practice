#include <vector>
#include <stack>
using namespace std;
class Solution {
    public:
        vector<int> nextGreaterElements(vector<int>& nums) {
            int n = nums.size();
            vector<int> ans(n, -1);
            stack<int> st;
    
            for (int i = 2 * n - 1; i >= 0; --i) {
                int curr = nums[i % n];
                while (!st.empty() && nums[st.top()] <= curr) {
                    st.pop();
                }
                if (i < n && !st.empty()) ans[i] = nums[st.top()];
    
                st.push(i % n);
            }
            return ans;
        }
    };