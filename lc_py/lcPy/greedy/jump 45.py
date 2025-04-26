from typing import List
class Jump:
    def jump(self,nums: List[int]) -> int:
        n = len(nums)

        end = 0
        maxPos = 0
        step = 0

        for i in range(n - 1):
            maxPos = max(maxPos,i + nums[i])
            if i == end:
                end = maxPos
                step += 1
        return step


if __name__ == "__main__":
    jump = Jump()
    nums = [2,3,1,1,4]
    print(jump.jump(nums))
