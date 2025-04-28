#include <iostream>
#include <vector>
//
// Created by 24276 on 2025/2/25.
//
class replace_elements1299 {
public:
    std::vector<int> replaceElements(std::vector<int>& arr) {
        int mx = arr[arr.size() - 1];
        arr[arr.size() - 1] = -1;
        for(int i = arr.size() - 2; i >= 0; --i) {
            auto pre_max = std::max(arr[i],mx);
            arr[i] = mx;
            mx = pre_max;
        }
        return arr;
    }
};

int main() {
    replace_elements1299 ps;
    std::vector<int> arr = {17,18,5,4,6,1};
    auto res = ps.replaceElements(arr);
    for(auto const& val : res) {
        std::cout << val << " ";
    }
    return 0;
}
