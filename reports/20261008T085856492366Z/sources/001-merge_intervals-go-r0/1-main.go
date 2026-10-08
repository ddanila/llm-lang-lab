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
	var n int
	var err error
	for {
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		if line == "" {
			break
		}
		n, err = strconv.Atoi(line)
		if err != nil {
			continue
		}
		break
	}
	
	if n < 0 || n > 200 {
		fmt.Println(0)
		return
	}
	
	intervals := make([][2]int, n)
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.Atoi(parts[0])
			r, _ := strconv.Atoi(parts[1])
			intervals[i] = [2]int{l, r}
		}
	}
	
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	// Sort intervals by L ascending
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			if intervals[j][0] > intervals[j+1][0] || 
			   (intervals[j][0] == intervals[j+1][0] && intervals[j][1] > intervals[j+1][1]) {
				intervals[j], intervals[j+1] = intervals[j+1], intervals[j]
			}
		}
	}
	
	// Merge overlapping intervals (closed intervals, overlap if they share any point)
	merged := make([][2]int, 0, n)
	if len(intervals) > 0 {
		current := intervals[0]
		for i := 1; i < n; i++ {
			next := intervals[i]
			// Overlap condition: current.L <= next.R && current.R >= next.L
			// Since we sorted by L, current.L <= next.L always, so we check if they overlap
			if current[0] <= next[1] { // They overlap or touch at a point
				// Merge them: new end is max(current.R, next.R)
				if next[1] > current[1] {
					current[1] = next[1]
				}
			} else {
				// No overlap, push current and start new
				merged = append(merged, current)
				current = next
			}
		}
		merged = append(merged, current)
	}
	
	fmt.Println(len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}