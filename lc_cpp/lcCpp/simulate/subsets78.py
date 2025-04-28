from typing import List
class Subsets:
    def subsets(self,nums:List[int]) ->List[List[int]]:
        res = []
        path = []
        n = len(nums)

        def dfs(start:int) -> None:
            res.append(path[:])     #使用path创建副本

            for i in range(start,n):
                path.append(nums[i])
                dfs(i + 1)
                path.pop()
        dfs(0)
        return res

if __name__ == '__main__':
    subsets = Subsets()
    result = subsets.subsets(nums=[1,2,3])
    print(result)
