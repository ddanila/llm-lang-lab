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
	var n int
	var err error
	
	for {
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		n, err = strconv.Atoi(line)
		if err != nil {
			continue
		}
		break
	}
	
	intervals := make([]struct{ L, R int64 }, 0, n)
	
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.ParseInt(parts[0], 10, 64)
			r, _ := strconv.ParseInt(parts[1], 10, 64)
			intervals = append(intervals, struct{ L, R int64 }{L: l, R: r})
		}
	}
	
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})
	
	merged := make([]struct{ L, R int64 }, 0, n)
	currentStart := intervals[0].L
	currentEnd := intervals[0].R
	
	for i := 1; i < n; i++ {
		next := &intervals[i]
		
		// Merge if overlapping (shared endpoints count as overlap)
		if next.L <= currentEnd {
			if next.R > currentEnd {
				currentEnd = next.R
			}
		} else {
			merged = append(merged, struct{ L, R int64 }{L: currentStart, R: currentEnd})
			currentStart = next.L
			currentEnd = next.R
		}
	}
	
	merged = append(merged, struct{ L, R int64 }{L: currentStart, R: currentEnd})
	
	fmt.Printf("%d\n", len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval.L, interval.R)
	}
}