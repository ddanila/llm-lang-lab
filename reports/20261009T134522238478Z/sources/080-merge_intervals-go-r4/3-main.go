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
			l, _ := strconv.ParseInt(fields[0], 10, 64)
			r, _ := strconv.ParseInt(fields[1], 10, 64)
			intervals[i].L = l
			intervals[i].R = r
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
		if len(merged) == 0 || merged[len(merged)-1].R < interval.L {
			// No overlap - there's a gap between them
			merged = append(merged, interval)
		} else {
			// Overlap or shared endpoint (interval.L <= merged.R)
			if merged[len(merged)-1].R < interval.R {
				merged[len(merged)-1].R = interval.R
			}
		}
	}
	
	// Output result
	fmt.Printf("%d\n", len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}