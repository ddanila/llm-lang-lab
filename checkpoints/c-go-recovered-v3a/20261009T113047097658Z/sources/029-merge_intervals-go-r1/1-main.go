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
	
	// Parse N from the line (may contain whitespace and newline)
	str := strings.TrimSpace(line)
	n, err := strconv.Atoi(str)
	if err != nil {
		fmt.Println(0)
		return
	}
	
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	intervals := make([]struct{ L, R int64 }, n)
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err.Error() != "EOF" {
			break
		}
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.Atoi(parts[0])
			r, _ := strconv.Atoi(parts[1])
			intervals[i] = struct{ L, R int64 }{int64(l), int64(r)}
		}
	}
	
	// Sort intervals by L (ascending), then by R (ascending) for stability
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[j].L < intervals[i].L || 
			   (intervals[j].L == intervals[i].L && intervals[j].R < intervals[i].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	// Merge overlapping intervals
	var merged []struct{ L, R int64 }
	if n > 0 {
		current := intervals[0]
		for i := 1; i < n; i++ {
			next := intervals[i]
			// Overlap if next.L <= current.R (since they are closed intervals)
			if next.L <= current.R {
				// Merge: extend the end if needed
				if next.R > current.R {
					current.R = next.R
				}
			} else {
				// No overlap, push current and start new
				merged = append(merged, current)
				current = next
			}
		}
		merged = append(merged, current)
	}
	
	// Output count
	fmt.Println(len(merged))
	// Output each interval
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}