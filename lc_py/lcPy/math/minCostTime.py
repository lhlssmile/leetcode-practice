def cost_for(startAt, moveCost, pushCost, m, s):
    time_str = f"{m:02d}{s:02d}"
    time_str = time_str.lstrip('0')
    if not time_str:
        time_str = "0"

    cur = str(startAt)
    cost = 0
    for c in time_str:
        if c != cur:
            cost += moveCost
            cur = c
        cost += pushCost
    return cost


if __name__ == "__main__":
    startAt = int(input())
    moveCost = int(input())
    pushCost = int(input())
    targetSeconds = int(input())

    res = float('inf')
    candidates = []
    mm, ss = divmod(targetSeconds, 60)

    if mm <= 99 and ss <= 99:
        candidates.append((mm, ss))
    if mm > 0 and ss + 60 <= 99:
        candidates.append((mm - 1, ss + 60))

    for m, s in candidates:
        res = min(res, cost_for(startAt, moveCost, pushCost, m, s))

    print(res)
