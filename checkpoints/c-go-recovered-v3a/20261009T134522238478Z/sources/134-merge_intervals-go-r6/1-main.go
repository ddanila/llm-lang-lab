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
	
	// Remove whitespace and parse N
	fields := strings.Fields(line)
	if len(fields) == 0 {
		fmt.Println("0")
		return
	}
	n, _ := strconv.Atoi(fields[0])

	intervals := make([]struct{ L, R int64 }, n)

	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && line != "" {
			break
		}
		fields = strings.Fields(line)
		if len(fields) >= 2 {
			intervals[i].L, _ = strconv.ParseInt(fields[0], 10, 64)
			intervals[i].R, _ = strconv.ParseInt(fields[1], 10, 64)
		}
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	// Sort intervals by L, then by R
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[j].L < intervals[i].L || (intervals[j].L == intervals[i].L && intervals[j].R < intervals[i].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}

	// Merge intervals
	if n > 0 {
		merged := make([]struct{ L, R int64 }, 0, n)
		current := intervals[0]
		for i := 1; i < n; i++ {
			next := intervals[i]
			// Overlap if next.L <= current.R (including shared endpoints)
			if next.L <= current.R {
				// Merge: extend R if needed
				if next.R > current.R {
					current.R = next.R
				}
			} else {
				merged = append(merged, current)
				current = next
			}
		}
		merged = append(merged, current)

		fmt.Printf("%d\n", len(merged))
		for _, m := range merged {
			fmt.Printf("%d %d\n", m.L, m.R)
		}
	}
}