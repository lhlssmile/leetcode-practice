if __name__ == '__main__':
    t = int(input())

    for _ in range(t):
        n = int(input())
        k = int(input())
        if n * n - 1 == k:
            print("No")
        else:
            for i in range(n):
                s = ""
                for j in range(n):
                    if k > 0:
                        s += 'U'
                        k -= 1
                    elif i == n - 1 and j == n - 1:
                        s += 'L'
                    elif i == n - 1:
                        s += 'R'
                    else:
                        s += 'D'
                print(s)