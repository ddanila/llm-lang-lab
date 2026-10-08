package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
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
	
	// Trim whitespace and parse N
	line = strings.TrimSpace(line)
	if line == "" {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}
	
	// Handle N=0 case
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	// Read N pairs
	intervals := make([][2]int64, n)
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.Atoi(parts[0])
			r, _ := strconv.Atoi(parts[1])
			intervals[i] = [2]int64{int64(l), int64(r)}
		}
	}
	
	// Sort intervals by L (ascending), then by R (ascending) for stability
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})
	
	// Merge overlapping intervals (including shared endpoints)
	var merged [][2]int64
	if len(intervals) > 0 {
		current := intervals[0]
		for i := 1; i < len(intervals); i++ {
			next := intervals[i]
			// Overlap if current.R >= next.L (since they are closed intervals)
			if current[1] >= next[0] {
				// Merge: extend the end if needed
				if next[1] > current[1] {
					current[1] = next[1]
				}
			} else {
				// No overlap, add current to merged and start new
				merged = append(merged, current)
				current = next
			}
		}
		// Add the last interval
		merged = append(merged, current)
	}
	
	// Output result
	fmt.Printf("%d\n", len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}