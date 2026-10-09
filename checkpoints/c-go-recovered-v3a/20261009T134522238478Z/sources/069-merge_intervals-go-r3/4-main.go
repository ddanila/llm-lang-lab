package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	var n int
	if _, err := fmt.Fscanf(reader, "%d", &n); err != nil {
		return
	}
	
	intervals := make([][2]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscanf(reader, "%d %d", &intervals[i][0], &intervals[i][1])
	}
	
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})
	
	type Interval struct {
		L, R int
	}
	var merged []Interval
	
	for _, interval := range intervals {
		if len(merged) == 0 {
			merged = append(merged, Interval{L: interval[0], R: interval[1]})
			continue
		}
		
		last := &merged[len(merged)-1]
		if interval[0] <= last.R {
			if interval[1] > last.R {
				last.R = interval[1]
			}
		} else {
			merged = append(merged, Interval{L: interval[0], R: interval[1]})
		}
	}
	
	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}