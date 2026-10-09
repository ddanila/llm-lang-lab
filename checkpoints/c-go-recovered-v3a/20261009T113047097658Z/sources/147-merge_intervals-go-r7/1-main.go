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

	var n int
	if s, err := reader.ReadString('\n'); err == nil {
		s = strings.TrimSpace(s)
		if s != "" {
			n, _ = strconv.Atoi(s)
		}
	} else {
		fmt.Println(0)
		return
	}

	intervals := make([]struct{ L, R int64 }, n)
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

	if n == 0 {
		fmt.Println(0)
		return
	}

	// Sort by L ascending, then R ascending
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[i].L > intervals[j].L || (intervals[i].L == intervals[j].L && intervals[i].R > intervals[j].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}

	merged := make([]struct{ L, R int64 }, 0, n)
	if n > 0 {
		current := intervals[0]
		for i := 1; i < n; i++ {
			next := intervals[i]
			// Merge if overlap or shared endpoint (L <= current.R)
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
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}