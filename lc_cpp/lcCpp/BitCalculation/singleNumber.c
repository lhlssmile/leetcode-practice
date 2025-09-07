#include <stdio.h>
#include <assert.h>

int singleNumber(int* nums, int numsSize) {
    int ans = 0;
    for (int i = 0; i < 32; i++) {
        int cnt1 = 0;
        for (int j = 0; j < numsSize; j++) {
            cnt1 += (nums[j] >> i) & 1;
        }
        ans |= (cnt1 % 3) << i;
    }
    return ans;
}

// 状态机解法
int singleNumberStateMachine(int* nums, int numsSize) {
    int ones = 0, twos = 0;
    for (int i = 0; i < numsSize; i++) {
        ones = (ones ^ nums[i]) & ~twos;
        twos = (twos ^ nums[i]) & ~ones;
    }
    return ones;
}

void test() {
    int nums1[] = {2, 2, 3, 2};
    assert(singleNumber(nums1, 4) == 3);
    
    int nums2[] = {0, 1, 0, 1, 0, 1, 99};
    assert(singleNumber(nums2, 7) == 99);
    
    printf("All tests passed!\n");
}

int main() {
    test();
    return 0;
}