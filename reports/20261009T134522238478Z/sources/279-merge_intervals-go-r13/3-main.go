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
	line = strings.TrimSpace(line)
	if line == "" {
		fmt.Println("0")
		return
	}
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}

	intervals := make([]struct {
		L, R int64
	}, n)

	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			intervals[i].L, _ = strconv.ParseInt(parts[0], 10, 64)
			intervals[i].R, _ = strconv.ParseInt(parts[1], 10, 64)
		}
	}

	// Sort by L ascending, then by R ascending
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[j].L < intervals[i].L || (intervals[j].L == intervals[i].L && intervals[j].R < intervals[i].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	merged := make([]struct {
		L, R int64
	}, 1)
	merged[0].L = intervals[0].L
	merged[0].R = intervals[0].R

	for i := 1; i < n; i++ {
		currIdx := len(merged) - 1
		next := intervals[i]

		// Merge if they overlap (next.L <= curr.R) - shared endpoints count as overlap
		if next.L <= merged[currIdx].R {
			// Extend the current interval to max(curr.R, next.R)
			if next.R > merged[currIdx].R {
				merged[currIdx].R = next.R
			}
		} else {
			merged = append(merged, struct{ L, R int64 }{L: next.L, R: next.R})
		}
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}