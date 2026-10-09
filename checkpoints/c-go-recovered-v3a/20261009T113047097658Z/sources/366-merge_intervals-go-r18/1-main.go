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
	
	// Clean the line and parse N
	line = strings.TrimSpace(line)
	if line == "" {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}

	intervals := make([][2]int64, 0)
	
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && line == "" {
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
		
		l, err1 := strconv.ParseInt(parts[0], 10, 64)
		r, err2 := strconv.ParseInt(parts[1], 10, 64)
		if err1 != nil || err2 != nil {
			continue
		}
		
		intervals = append(intervals, [2]int64{l, r})
	}

	if len(intervals) == 0 {
		fmt.Println("0")
		return
	}

	// Sort by L ascending, then by R ascending
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})

	// Merge intervals
	var merged []int64
	currentStart := intervals[0][0]
	currentEnd := intervals[0][1]

	for i := 1; i < len(intervals); i++ {
		nextL := intervals[i][0]
		nextR := intervals[i][1]

		// Merge if overlapping (including shared endpoints)
		if nextL <= currentEnd {
			if nextR > currentEnd {
				currentEnd = nextR
			}
		} else {
			merged = append(merged, currentStart, currentEnd)
			currentStart = nextL
			currentEnd = nextR
		}
	}
	merged = append(merged, currentStart, currentEnd)

	fmt.Println(len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}