#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
class intersectSolution{
public:
    //common condition
    std::vector<int> intersect(std::vector<int> &nums1,std::vector<int> &nums2) {
        //if arrays are sorted then skip the next 2 lines./
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        int nums1SubScript = 0, nums2SubScript = 0;
        std::vector<int> res;
        //Time complexity O(n)
        while (nums1SubScript < nums1.size() && nums2SubScript < nums2.size()) {
            if (nums1[nums1SubScript] == nums2[nums2SubScript]) {
                res.emplace_back(nums1[nums1SubScript]); // 记录交集元素
                nums1SubScript++; // 移动 nums1 指针
                nums2SubScript++; // 移动 nums2 指针
            } else if (nums1[nums1SubScript] < nums2[nums2SubScript]) {
                nums1SubScript++;
            } else {
                nums2SubScript++;
            }
        }
        return res;
    }
    //nums1.size() < nums2.size()?
    std::vector<int> intersectSorted(std::vector<int> &nums1,std::vector<int> &nums2){
        if (nums1.size() < nums2.size()) return intersectSorted(nums2,nums1);
        std::unordered_map<int,int> count;
        for(auto num : nums1){
            //record elements appear times
            count[num]++;
        }
        std::vector<int> res;
        for(auto num : nums2){
            if(count[num] > 0){
                res.push_back(num);
                count[num]--; //insert times control,according to nums1 ele appear times
            }
        }
        return res;
    }
};
int main() {
    intersectSolution ps;
    std::vector<int> nums1 = {1,2,2,1}; std::vector<int> nums2 = {2,2};
    std::vector<int> res = ps.intersectSorted(nums1,nums2);
    std::cout << "[";
    for (auto i = 0; i < res.size(); i++) {
        std::cout << res[i];
        if (i != res.size() - 1) std::cout << ",";
    }
    std::cout << "]" << std::endl;
    return 0;
}
