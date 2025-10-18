from typing import List

class Solution:
    def robot(self, command: str, obstacles: List[List[int]], x: int, y: int) -> bool:
        # 1. 模拟一轮 command 的路径
        path = []
        cx, cy = 0, 0
        for c in command:
            if c == 'U':
                cy += 1
            else:  # 'R'
                cx += 1
            path.append((cx, cy))
        dx, dy = cx, cy  # 一轮的位移

        def reachable(tx: int, ty: int) -> bool:
            if tx < 0 or ty < 0:
                return False
            for px, py in path:
                rx, ry = tx - px, ty - py
                if rx < 0 or ry < 0:
                    continue
                if dx == 0 and rx != 0:
                    continue
                if dy == 0 and ry != 0:
                    continue
                if (dx == 0 or rx % dx == 0) and (dy == 0 or ry % dy == 0):
                    kx = rx // dx if dx else ry // dy
                    ky = ry // dy if dy else rx // dx
                    if kx == ky:
                        return True
            return False

        # 2. 检查终点
        if not reachable(x, y):
            return False

        # 3. 检查障碍物
        for ox, oy in obstacles:
            if ox > x or oy > y:
                continue
            if reachable(ox, oy):
                return False
        return True


if __name__ == '__main__':
    command = "URR"
    obstacles = [[2, 2]]
    # obstacles = [[7, 7], [0, 5], [2, 7], [8, 6], [8, 7], [6, 5], [4, 4], [0, 3], [3, 6]]
    x, y = 3, 2

    s = Solution()
    print(s.robot(command, obstacles, x, y))