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
	
	// Merge overlapping intervals
	// Two closed intervals [a,b] and [c,d] (with a <= c) overlap if c <= b
	// They are merely adjacent (not overlapping) if c = b + 1
	// So merge if c <= b AND c != b + 1, which simplifies to c <= b for integers
	// Wait, let me reconsider...
	
	// Actually for closed intervals in integer space:
	// [1,2] contains {1, 2}
	// [3,4] contains {3, 4}
	// They don't share any element, so they don't overlap
	// The condition c <= b means the start of second is <= end of first
	// For [1,2] and [3,4]: c=3, b=2, so c > b, no overlap - correct!
	// For [1,3] and [2,4]: c=2, b=3, so c <= b, they overlap - correct!
	
	merged := make([][2]int, 0, n)
	if len(intervals) > 0 {
		current := intervals[0]
		for i := 1; i < n; i++ {
			next := intervals[i]
			// Check if they overlap: next.L <= current.R
			if next[0] <= current[1] {
				// They overlap, merge them
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