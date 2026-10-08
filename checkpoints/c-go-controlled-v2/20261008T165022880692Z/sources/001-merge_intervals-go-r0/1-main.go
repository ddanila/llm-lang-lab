package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read N
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	// Remove whitespace and parse N
	line = strings.TrimSpace(line)
	if line == "" {
		fmt.Println(0)
		return
	}
	
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}
	
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	// Read N pairs of intervals
	intervals := make([][2]int, n)
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.Atoi(parts[0])
			r, _ := strconv.Atoi(parts[1])
			intervals[i] = [2]int{l, r}
		}
	}
	
	// Sort intervals by L, then by R (though primary sort key is L)
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[j][0] < intervals[i][0] || 
			   (intervals[j][0] == intervals[i][0] && intervals[j][1] < intervals[i][1]) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	// Merge overlapping intervals
	if len(intervals) == 0 {
		fmt.Println(0)
		return
	}
	
	var merged [][2]int
	merged = append(merged, intervals[0])
	
	for i := 1; i < n; i++ {
		last := &merged[len(merged)-1]
		current := &intervals[i]
		
		// Check if they overlap (including shared endpoints)
		if current[0] <= last[1] {
			// Overlapping, merge by taking max of R
			if current[1] > last[1] {
				last[1] = current[1]
			}
		} else {
			// Non-overlapping, add new interval
			merged = append(merged, *current)
		}
	}
	
	fmt.Println(len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}