package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	var N int
	if !scanner.Scan() {
		return
	}
	N, _ = strconv.Atoi(strings.TrimSpace(scanner.Text()))

	intervals := make([]struct{ L, R int64 }, 0, N)
	for i := 0; i < N; i++ {
		if !scanner.Scan() {
			break
		}
		line := strings.TrimSpace(scanner.Text())
		fields := strings.Fields(line)
		if len(fields) >= 2 {
			L, _ := strconv.ParseInt(fields[0], 10, 64)
			R, _ := strconv.ParseInt(fields[1], 10, 64)
			intervals = append(intervals, struct{ L, R int64 }{L, R})
		}
	}

	if N == 0 {
		fmt.Println(0)
		return
	}

	// Sort by L ascending, then by R ascending
	for i := 0; i < len(intervals)-1; i++ {
		for j := i + 1; j < len(intervals); j++ {
			if intervals[i].L > intervals[j].L || (intervals[i].L == intervals[j].L && intervals[i].R > intervals[j].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}

	merged := make([]struct{ L, R int64 }, 0, N)
	if len(intervals) > 0 {
		current := intervals[0]
		for i := 1; i < len(intervals); i++ {
			next := intervals[i]
			if next.L <= current.R { // Overlap including shared endpoints
				if next.R > current.R {
					current.R = next.R
				}
			} else {
				merged = append(merged, current)
				current = next
			}
		}
		merged = append(merged, current)
	}

	fmt.Printf("%d\n", len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}