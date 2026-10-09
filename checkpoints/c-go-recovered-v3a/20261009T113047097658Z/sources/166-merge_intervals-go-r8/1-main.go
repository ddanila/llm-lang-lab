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
	
	var n int
	var err error
	
	if token, err := reader.ReadString('\n'); err == nil {
		token = strings.TrimSpace(token)
		if token != "" {
			n, _ = strconv.Atoi(token)
		}
	}
	
	intervals := make([]struct{ L, R int64 }, n)
	
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		fields := strings.Fields(line)
		if len(fields) >= 2 {
			l, _ := strconv.ParseInt(fields[0], 10, 64)
			r, _ := strconv.ParseInt(fields[1], 10, 64)
			intervals[i] = struct{ L, R int64 }{L: l, R: r}
		}
	}
	
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	// Sort by L ascending
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[i].L > intervals[j].L || (intervals[i].L == intervals[j].L && intervals[i].R > intervals[j].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	merged := make([]struct{ L, R int64 }, 0, n)
	if n > 0 {
		current := intervals[0]
		for i := 1; i < n; i++ {
			next := intervals[i]
			if next.L <= current.R+1 {
				// Overlap or adjacent (but problem says NOT merely adjacent integers)
				// Wait, let me re-read: "including shared endpoints, but NOT merely adjacent integers"
				// This means [1,2] and [3,4] should NOT be merged because they don't overlap
				// They are adjacent but not overlapping. Overlap means they share at least one point.
				// So [1,2] and [2,3] would merge to [1,3] because they share 2.
				// [1,2] and [3,4] don't share any point, so no merge.
				// The condition is next.L <= current.R (for overlap)
				if next.L <= current.R {
					current.R = max(current.R, next.R)
				} else {
					merged = append(merged, current)
					current = next
				}
			} else {
				merged = append(merged, current)
				current = next
			}
		}
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