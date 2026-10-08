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

	intervals := make([]struct{ L, R int64 }, n)
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && i < n-1 {
			break
		}
		fields := strings.Fields(line)
		var l, r int64
		l, _ = strconv.ParseInt(fields[0], 10, 64)
		r, _ = strconv.ParseInt(fields[1], 10, 64)
		intervals[i] = struct{ L, R int64 }{L: l, R: r}
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	// Sort by L ascending, then R ascending
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[j].L < intervals[i].L || (intervals[j].L == intervals[i].L && intervals[j].R < intervals[i].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}

	// Merge intervals
	merged := make([]struct{ L, R int64 }, 0, n)
	if len(intervals) > 0 {
		currentL, currentR := intervals[0].L, intervals[0].R
		for i := 1; i < n; i++ {
			nextL, nextR := intervals[i].L, intervals[i].R
			// Overlap if nextL <= currentR (closed intervals)
			if nextL <= currentR {
				if nextR > currentR {
					currentR = nextR
				}
			} else {
				merged = append(merged, struct{ L, R int64 }{L: currentL, R: currentR})
				currentL, currentR = nextL, nextR
			}
		}
		merged = append(merged, struct{ L, R int64 }{L: currentL, R: currentR})
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}