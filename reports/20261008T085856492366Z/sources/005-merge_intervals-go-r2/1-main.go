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
	if !scanner.Scan() {
		return
	}
	line := strings.TrimSpace(scanner.Text())
	if line == "" {
		fmt.Println(0)
		return
	}
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}

	intervals := make([]struct{ L, R int64 }, 0, n)
	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		tokens := strings.Fields(scanner.Text())
		if len(tokens) >= 2 {
			l, _ := strconv.ParseInt(tokens[0], 10, 64)
			r, _ := strconv.ParseInt(tokens[1], 10, 64)
			intervals = append(intervals, struct{ L, R int64 }{L: l, R: r})
		}
	}

	if len(intervals) == 0 {
		fmt.Println(0)
		return
	}

	// Sort by L ascending, then by R ascending
	for i := 0; i < len(intervals)-1; i++ {
		for j := i + 1; j < len(intervals); j++ {
			if intervals[j].L < intervals[i].L || (intervals[j].L == intervals[i].L && intervals[j].R < intervals[i].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}

	merged := make([]struct{ L, R int64 }, 0, len(intervals))
	current := intervals[0]
	for i := 1; i < len(intervals); i++ {
		next := intervals[i]
		// Merge if overlap: next.L <= current.R
		if next.L <= current.R {
			if next.R > current.R {
				current.R = next.R
			}
		} else {
			merged = append(merged, current)
			current = next
		}
	}
	merged = append(merged, current)

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}