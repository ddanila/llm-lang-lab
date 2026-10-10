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
	line = strings.TrimSpace(line)
	if line == "" {
		fmt.Println("0")
		return
	}
	n, err := strconv.Atoi(line)
	if err != nil {
		// Try to parse from full input if first line is not clean
		allInput, _ := reader.ReadString('\n')
		allInput = strings.TrimSpace(allInput)
		n, _ = strconv.Atoi(allInput)
	}

	var intervals []struct{ L, R int64 }
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
		l, _ := strconv.ParseInt(parts[0], 10, 64)
		r, _ := strconv.ParseInt(parts[1], 10, 64)
		intervals = append(intervals, struct{ L, R int64 }{L: l, R: r})
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	var merged []struct{ L, R int64 }
	start := intervals[0].L
	end := intervals[0].R

	for i := 1; i < len(intervals); i++ {
		if intervals[i].L <= end {
			if intervals[i].R > end {
				end = intervals[i].R
			}
		} else {
			merged = append(merged, struct{ L, R int64 }{L: start, R: end})
			start = intervals[i].L
			end = intervals[i].R
		}
	}
	merged = append(merged, struct{ L, R int64 }{L: start, R: end})

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}