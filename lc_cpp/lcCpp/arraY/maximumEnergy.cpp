#include <climits>
#include <iostream>
#include <vector>
//
// Created by 24276 on 2025/10/10.
//
class maximum_energy {
public:
    int maximumEnergy(std::vector<int>& energy, int k) {
        int n = energy.size();

        for (int i = n - k - 1; i >= 0; i--) {
            energy[i] += energy[i + k];
        }

        return *std::max_element(energy.begin(), energy.end());
    }
};

int main() {
    std::vector<int> energy = {5, 2, -10, -5, 1};
    int k = 3;
    maximum_energy s;
    std::cout << s.maximumEnergy(energy, k);
    return 0;
}
