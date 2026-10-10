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
	input, _ := os.ReadFile("/dev/stdin")
	tokens := strings.Fields(string(input))
	if len(tokens) == 0 {
		fmt.Println("0")
		return
	}

	n, _ := strconv.Atoi(tokens[0])
	intervals := make([][2]int, 0)

	idx := 1
	for i := 0; i < n && idx+1 <= len(tokens); i++ {
		l, _ := strconv.Atoi(tokens[idx])
		r, _ := strconv.Atoi(tokens[idx+1])
		intervals = append(intervals, [2]int{l, r})
		idx += 2
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})

	if len(intervals) == 0 {
		fmt.Println("0")
		return
	}

	merged := make([][2]int, 0)
	currentStart := intervals[0][0]
	currentEnd := intervals[0][1]

	for i := 1; i < len(intervals); i++ {
		if intervals[i][0] <= currentEnd {
			if intervals[i][1] > currentEnd {
				currentEnd = intervals[i][1]
			}
		} else {
			merged = append(merged, [2]int{currentStart, currentEnd})
			currentStart = intervals[i][0]
			currentEnd = intervals[i][1]
		}
	}
	merged = append(merged, [2]int{currentStart, currentEnd})

	fmt.Println(len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}