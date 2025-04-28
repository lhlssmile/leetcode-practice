#include <vector>
#include <iostream>
using namespace std;

class find_median_sorted_arrays4 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalSize = nums1.size() + nums2.size();
        
        // 如果总长度是奇数，中位数是第(totalSize/2+1)小的元素
        if (totalSize % 2 == 1) {
            return findKthElement(nums1, nums2, (totalSize / 2) + 1);
        } 
        // 如果总长度是偶数，中位数是第(totalSize/2)和第(totalSize/2+1)小的元素的平均值
        else {
            return (findKthElement(nums1, nums2, totalSize / 2) + 
                   findKthElement(nums1, nums2, (totalSize / 2) + 1)) / 2.0;
        }
    }
    
private:
    // 寻找两个有序数组中的第k小元素
    int findKthElement(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        int index1 = 0, index2 = 0;
        
        while (true) {
            // 边界情况
            if (index1 == m) {
                return nums2[index2 + k - 1];
            }
            if (index2 == n) {
                return nums1[index1 + k - 1];
            }
            if (k == 1) {
                return min(nums1[index1], nums2[index2]);
            }
            
            // 正常情况，取k/2-1 位置的元素进行比较
            int newIndex1 = min(index1 + k/2 - 1, m - 1);
            int newIndex2 = min(index2 + k/2 - 1, n - 1);
            int pivot1 = nums1[newIndex1];
            int pivot2 = nums2[newIndex2];
            
            if (pivot1 <= pivot2) {
                // 排除nums1[index1]到nums1[newIndex1]的元素
                k -= (newIndex1 - index1 + 1);
                index1 = newIndex1 + 1;
            } else {
                // 排除nums2[index2]到nums2[newIndex2]的元素
                k -= (newIndex2 - index2 + 1);
                index2 = newIndex2 + 1;
            }
        }
    }
};

int main() {
    find_median_sorted_arrays4 solution;
    
    // 示例1
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    cout << "Example 1: " << solution.findMedianSortedArrays(nums1, nums2) << endl; // 输出: 2.0
    
    // 示例2
    vector<int> nums3 = {1, 2};
    vector<int> nums4 = {3, 4};
    cout << "Example 2: " << solution.findMedianSortedArrays(nums3, nums4) << endl; // 输出: 2.5
    
    return 0;
}