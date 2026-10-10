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
	
	// Parse N from the line (handle potential whitespace)
	fields := strings.Fields(line)
	if len(fields) == 0 {
		fmt.Println("0")
		return
	}
	n, err := strconv.Atoi(fields[0])
	if err != nil {
		return
	}
	
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	// Read N pairs
	intervals := make([]struct{ L, R int64 }, n)
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && line != "" {
			break
		}
		fields = strings.Fields(line)
		if len(fields) >= 2 {
			intervals[i].L, _ = strconv.Atoi(fields[0])
			intervals[i].R, _ = strconv.Atoi(fields[1])
		}
	}
	
	// Sort by L, then by R
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})
	
	// Merge intervals
	var merged []struct{ L, R int64 }
	for _, interval := range intervals {
		if len(merged) == 0 || merged[len(merged)-1].R < interval.L-1 {
			// No overlap (or just adjacent integers, which doesn't count as overlapping)
			merged = append(merged, interval)
		} else {
			// Overlap or shared endpoint
			merged[len(merged)-1].R = max(merged[len(merged)-1].R, interval.R)
		}
	}
	
	// Output result
	fmt.Printf("%d\n", len(merged))
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