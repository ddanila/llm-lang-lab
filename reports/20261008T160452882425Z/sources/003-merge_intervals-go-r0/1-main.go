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
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	// Handle whitespace and empty input
	input = strings.TrimSpace(input)
	if input == "" {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(strings.Split(input, "\n")[0])
	if err != nil {
		// Try reading more if first line is not a number
		return
	}
	
	var intervals []struct {
		L, R int64
	}
	
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
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
		
		l, err := strconv.ParseInt(parts[0], 10, 64)
		if err != nil {
			continue
		}
		
		r, err := strconv.ParseInt(parts[1], 10, 64)
		if err != nil {
			continue
		}
		
		intervals = append(intervals, struct{ L, R int64 }{l, r})
	}
	
	if n == 0 || len(intervals) == 0 {
		fmt.Println("0")
		return
	}
	
	// Sort intervals by L ascending, then by R ascending
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})
	
	// Merge overlapping intervals
	var merged []struct {
		L, R int64
	}
	
	if len(intervals) > 0 {
		current := intervals[0]
		
		for i := 1; i < len(intervals); i++ {
			next := intervals[i]
			
			// Overlap condition: current.R >= next.L (closed intervals, shared endpoints overlap)
			if current.R >= next.L {
				// Merge
				current.R = max(current.R, next.R)
			} else {
				// No overlap, add current and move to next
				merged = append(merged, current)
				current = next
			}
		}
		
		// Add the last interval
		merged = append(merged, current)
	}
	
	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}

func max(a, b int64) int64 {
	if a > b {
		return a
	}
	return b
}