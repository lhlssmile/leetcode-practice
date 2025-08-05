//
// Created by 24276 on 2025/8/5.
//

#include <vector>
using namespace std;

class num_of_unplaced_fruits {
public:
    int numOfUnplacedFruits (vector<int>& fruits, vector<int>& baskets) {
        int n = baskets.size();
        vector<int> allocated(n, false);

        for (int x : fruits) {
            for (int i = 0; i < n; i++) {
                if (x <= baskets[i] && allocated[i] == false) {
                    allocated[i] = true;
                    break;
                }
            }
        }
        int ans = 0;
        for (auto x : allocated) {
            if (x == false) ans++;
        }
        return ans;
    }
};

int main() {
    vector<int> fruits = {4, 2, 5};
    vector<int> baskets = {3, 5, 4};
    num_of_unplaced_fruits ps;
    ps.numOfUnplacedFruits(fruits, baskets);
    return 0;
}

