from typing import List


class Solution:
    def maxFreeTime(self, eventTime: int, k: int, startTime: List[int], endTime: List[int]) -> int:
        '''
        重新安排会议 不要有交集 不要改变时长
        '''
        n = len(startTime)
        # n个会议 n+1 个空闲
        free = [0] * (n + 1)

        free[0] = startTime[0]  # 最左侧 ps:startTime = 0?

        for i in range(1,n):
            free[i] = startTime[i] - endTime[i - 1]
        free[n] = eventTime - endTime[-1]

        ans = s = 0

        for i,f in enumerate(free):
            s += f
            if i < k:
                continue
            ans = max(ans,s)
            s -= free[i - k]
        return ans


if __name__ == '__main__':
    s = Solution()
    print(s.maxFreeTime(5, 1, [1, 3], [2, 5]))
    