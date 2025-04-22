#include <iostream>
#include <unordered_set>

class minimum_sum2829 {
public:
    /**
     * greedy:
     *      1.use set? pair OR subArray?
     *      2.when a pair of integer greater than k,then no need to find,increment directly?
     * @param n return length == n k-avoiding array' sum(minimum)
     * @param k can not exist any subArray's sum equals with k
     * @return
     */
    int minimumSum(int n,int k) {
        //mine understanding? do not exist pair<int,int> equals k
        std::unordered_set<int> st;
        //directly insert minimum value & n(length) - 1
        int ans = 0,start_value = 1,count = 0;
        while(count < n) {
            if(st.find(k - start_value) == st.end()) {
                st.insert(start_value);
                ans += start_value;
                ++count;
            }
            start_value++;
        }
        return ans;
    }
};

int main() {
    minimum_sum2829 solution;
    std::cout << solution.minimumSum(3,5) << std::endl;
    return 0;
}
