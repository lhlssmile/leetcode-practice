#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;
class Solution {
    public:
        vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
            unordered_map<int, int> next;
            stack<int> st;
            
            for (auto x : nums2 ) {
                while(!st.empty() && x > st.top()) {
                    int prev = st.top();
                    st.pop();
                    next[prev] = x;
                }
                st.push(x);
            }
            vector<int> ans(nums1.size(), -1);
            for (int i = 0; i < nums1.size();i++) {
                if (next.count(nums1[i])) ans[i] = next[nums1[i]];
            }
            return ans;
        }
    };