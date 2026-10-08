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
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	// Trim and parse N
	line = strings.TrimSpace(line)
	if line == "" {
		return
	}
	n, _ = strconv.Atoi(line)

	intervals := make([][2]int, 0, n)

	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.Atoi(parts[0])
			r, _ := strconv.Atoi(parts[1])
			intervals = append(intervals, [2]int{l, r})
		}
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	// Sort intervals by start time (L), then by end time (R)
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})

	// Merge overlapping intervals
	var merged [][]int
	if len(intervals) > 0 {
		currentStart := intervals[0][0]
		currentEnd := intervals[0][1]

		for i := 1; i < len(intervals); i++ {
			nextStart, nextEnd := intervals[i][0], intervals[i][1]
			if nextStart <= currentEnd {
				// Overlap or shared endpoint -> merge
				if nextEnd > currentEnd {
					currentEnd = nextEnd
				}
			} else {
				// No overlap -> finalize current interval
				merged = append(merged, []int{currentStart, currentEnd})
				currentStart = nextStart
				currentEnd = nextEnd
			}
		}
		// Add the last interval
		merged = append(merged, []int{currentStart, currentEnd})
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m[0], m[1])
	}
}