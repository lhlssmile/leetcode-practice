#include <vector>
#include <iostream>
using namespace std;
class minimum_size1760 {
public:
    static int minimumSize(vector<int>& nums,int maxOperations) {
        int left = 1,right = *max_element(nums.begin(),nums.end());
        while(left < right) {
            int mid = left + (right - left ) / 2;
            if(canSplit(nums,maxOperations,mid)) {
                right = mid;
            }else {
                left = mid + 1;
            }
        }
        return left;
    }
    //开区间
    static int minimumSizeMine(vector<int>& nums,int maxOperations) {
        auto check = [&](int m) -> bool {
            long long count = 0;
            for(int x : nums) {
                count += (x - 1) / m;
            }
            return count <= maxOperations;
        };
        int left = 0,right = ranges::max(nums);
        while(left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? right : left ) = mid;
        }
        return right;
    }
    static int minimumSizeMine2(vector<int>& nums,int maxOperations) {
        //左闭区间右开区间
        int left = 1,right = ranges::max(nums);
        auto check = [&](int m) ->bool {
          int operations = 0;
            for(int x : nums) {
                if(x > m) {
                    operations += ( x - 1) / m;
                }
            }
            return operations <= maxOperations;
        };
        while(left < right) {
            int m = left + (right - left ) / 2;
            if(check(m)) {
                right = m;
            }else {
                left = m + 1;
            }
        }
        return left;
    }
private:
    static bool canSplit(vector<int>& nums,int maxOperations,int maxSize) {
        int operations = 0;
        for(int num : nums) {
            if(num > maxSize) {
                operations += (num - 1) / maxSize;
            }
        }
    return operations <= maxOperations;
    }

};



int main() {
    minimum_size1760 ps;
    std::vector<int> nums = {9,12,15,19};int maxOperations = 3;
    int minimumCost = ps.minimumSizeMine2(nums,maxOperations);
    std::cout << minimumCost << std::endl;
    return 0;
}
