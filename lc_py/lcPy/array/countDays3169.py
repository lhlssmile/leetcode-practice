import typing


class Solution:
    def countDays(self, days: int, meetings: typing.List[typing.List[int]])-> int:

        busy = [False] * len(days + 1)

        for start, end in meetings:
            for day in range(start,end + 1):
                if day <= days:
                    busy[day] = True

        free_days = 0

        for day in range(1,days + 1):
            if not busy[day]:
                free_days += 1

        return free_days
