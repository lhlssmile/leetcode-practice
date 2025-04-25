class MinCosts:
    def minCosts(self, cost: List[int]) -> List[int]:
        for i in range(1, len(cost)):
            cost[i] = min(cost[i], cost[i - 1])
        return cost



if __name__ == "__main__":

    sol = MinCosts()
    cost = [5,3,1,2,4]
    print(sol.minCosts(cost))