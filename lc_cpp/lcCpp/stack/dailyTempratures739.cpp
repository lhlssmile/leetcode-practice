//
// Created by 24276 on 2025/3/26.
//

#include <vector>
#include <iostream>
#include <stack>
using namespace std;
class daily_tempratures739 {
public:
    /**
     *
     * @param temperatures given temperatures several days
     * @return return an array means how long will temperature hotter than today?
     */
    static vector<int> dailyTemperatures(vector<int>& temperatures) {
        // stack<int> st;
        auto n = temperatures.size();
        vector<int> ans(n,0);
        for(int i = 0;i < temperatures.size();++i) {
            for(int j = i + 1;j < temperatures.size();j++) {
                if(temperatures[j] > temperatures[i]) {
                    ans[i] = j - i;
                    break;
                }
            }
        }
        return ans;
    }
    static vector<int> dailyTemperaturesa(vector<int>& temperatures) {
        auto n = temperatures.size();
        vector<int> ans(n,0);
        // use stack to store index
        stack<int> st;
        for(int i = 0;i < n;++i) {
            //碰到大于今天温度的就出栈今天 -> record as oneDay,入栈 oneDay
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prev = st.top();
                st.pop();
                ans[prev] = i - prev;
            }
            st.push(i);
        }
        return ans;
    }
};

int main() {
    daily_tempratures739 solution;
    vector<int> temperatures = {73,74,75,71,69,72,76,73};
    auto res = solution.dailyTemperaturesa(temperatures);
    for(auto after_day : res) {
        cout << after_day << " ";
    }
    return 0;
}
