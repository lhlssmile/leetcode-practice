from typing import List
class FirstMissingPositive:
    def firstMissingPositive(self,nums:List[int])-> int:
        n = len(nums)
        # 调整为正确位置 即value 出现在value - 1的索引位置
        for i in range(n):
            while 0 < nums[i] <= n and nums[i] != nums[nums[i] - 1]:
                nums[nums[i] - 1],nums[i] = nums[i],nums[nums[i] - 1]
        for i in range(n):
            if nums[i] != i + 1:
                return i + 1
        return n + 1
if __name__ == '__main__':
    first_missing_positive = FirstMissingPositive()
    res = first_missing_positive.firstMissingPositive(nums=[3,4,-1,1])
    print(res)