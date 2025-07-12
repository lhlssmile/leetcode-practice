import typing

class Solution:
	def countDays(self,days: int, meetings: List[List[int]]) ->int:
		if not meetings:
			return days
		
		meetings.sort()
		
		merged = []
		
		for start,end in meetings:
			if merged and start <= merged[-1][1]
				merged[-1][1] = max(merged[-1][1],end)
			else:
				merged.append([start,end])
		occupied_days = 0

		for start,end in merged:
			occupied_days += end - start + 1

		return days - occupied
