package main

type recorder struct {
	sc, t int
}
type ExamTracker struct {
	mp map[int]recorder
}

func NewExamTracker() ExamTracker {
	return ExamTracker{
		mp: make(map[int]recorder),
	}
}
func (ex *ExamTracker) Record(time, score int) {
	// 记录到hashtable
	ex.mp[time] = recorder{
		sc: score, t: time,
	}
}
func (ex *ExamTracker) TotalScore(startTime, endTime int) int64 {
	//遍历 table找到符合{start end的time}
	var total int64
	for time, rec := range ex.mp {
		if time >= startTime && time <= endTime {
			total += int64(rec.sc)
		}
	}
	return total
}
