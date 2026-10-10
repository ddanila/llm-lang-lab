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
	
	// Handle empty input or just whitespace
	line = strings.TrimSpace(line)
	if line == "" {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(line)
	if err != nil {
		// If first line is not N, try to parse from subsequent lines
		// But spec says "Read N", so we assume it's the first token
		fmt.Println("0")
		return
	}
	
	intervals := make([][2]int, 0)
	
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err.Error() != "EOF" {
			break
		}
		
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		
		parts := strings.Fields(line)
		if len(parts) < 2 {
			continue
		}
		
		l, err := strconv.Atoi(parts[0])
		if err != nil {
			continue
		}
		
		r, err := strconv.Atoi(parts[1])
		if err != nil {
			continue
		}
		
		intervals = append(intervals, [2]int{l, r})
	}
	
	// Sort intervals by L (ascending), then by R
	for i := 0; i < len(intervals)-1; i++ {
		for j := i + 1; j < len(intervals); j++ {
			if intervals[j][0] < intervals[i][0] || 
			   (intervals[j][0] == intervals[i][0] && intervals[j][1] < intervals[i][1]) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	// Merge intervals
	if len(intervals) == 0 {
		fmt.Println("0")
		return
	}
	
	merged := make([][2]int, 0)
	current := intervals[0]
	merged = append(merged, current)
	
	for i := 1; i < len(intervals); i++ {
		next := intervals[i]
		
		// Check if they overlap (including shared endpoints)
		// Overlap condition: next.L <= current.R
		if next[0] <= merged[len(merged)-1][1] {
			// Merge: extend the end if needed
			end := merged[len(merged)-1][1]
			if next[1] > end {
				merged[len(merged)-1][1] = next[1]
			}
		} else {
			// No overlap, add new interval
			merged = append(merged, next)
		}
	}
	
	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m[0], m[1])
	}
}