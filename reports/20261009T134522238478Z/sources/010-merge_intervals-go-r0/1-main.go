package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	
	if !scanner.Scan() {
		return
	}
	
	n, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil {
		return
	}
	
	intervals := make([][2]int64, 0)
	
	for i := 0; i < n; i++ {
		scanner.Scan()
		line := strings.TrimSpace(scanner.Text())
		parts := strings.Fields(line)
		
		if len(parts) >= 2 {
			l, _ := strconv.ParseInt(parts[0], 10, 64)
			r, _ := strconv.ParseInt(parts[1], 10, 64)
			intervals = append(intervals, [2]int64{l, r})
		}
	}
	
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	sort := func(a, b int64) bool { return a < b }
	
	// Sort intervals by start point
	for i := 1; i < len(intervals); i++ {
		for j := 0; j < i; j++ {
			if sort(intervals[i][0], intervals[j][0]) || 
			   (sort(intervals[i][0], intervals[j][0]) && intervals[i][0] == intervals[j][0] && sort(intervals[i][1], intervals[j][1])) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	if len(intervals) == 0 {
		fmt.Println("0")
		return
	}
	
	merged := make([][2]int64, 0)
	merged = append(merged, intervals[0])
	
	for i := 1; i < len(intervals); i++ {
		last := merged[len(merged)-1]
		
		// Overlap condition: start of current <= end of last
		if intervals[i][0] <= last[1] {
			// Merge: extend the end if needed
			newEnd := last[1]
			if intervals[i][1] > newEnd {
				newEnd = intervals[i][1]
			}
			merged[len(merged)-1] = [2]int64{last[0], newEnd}
		} else {
			// No overlap, add as new interval
			merged = append(merged, intervals[i])
		}
	}
	
	fmt.Println(len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}