class Solution:
    def maxBottlesDrunk(self, numBottles, numExchanges: int) -> int:
        if numBottles < numExchanges: return numBottles
        drunk = emp = numBottles
        while emp >= numExchanges:
            emp -= numExchanges - 1
            drunk += 1
            numExchanges += 1

        return drunk


if __name__ == '__main__':
    s = Solution()
    print(s.maxBottlesDrunk(13, 6))
    print(s.maxBottlesDrunk(1, 100))
    print(s.maxBottlesDrunk(10, 3))

