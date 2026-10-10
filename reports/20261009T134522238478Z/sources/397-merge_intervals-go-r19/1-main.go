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
	
	// Split line and parse N
	tokens := strings.Fields(line)
	if len(tokens) == 0 {
		return
	}
	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		return
	}

	var intervals []struct {
		L int64
		R int64
	}

	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		tokens = strings.Fields(line)
		if len(tokens) >= 2 {
			l, _ := strconv.ParseInt(tokens[0], 10, 64)
			r, _ := strconv.ParseInt(tokens[1], 10, 64)
			intervals = append(intervals, struct{ L, R int64 }{L: l, R: r})
		}
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	// Sort intervals by L, then by R
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	// Merge intervals
	var merged []struct {
		L int64
		R int64
	}
	
	if len(intervals) > 0 {
		current := intervals[0]
		for i := 1; i < len(intervals); i++ {
			next := intervals[i]
			// Check if intervals overlap or share an endpoint
			// They overlap if current.R >= next.L - 1 (since we need shared endpoints to merge)
			// Actually, the problem says "including shared endpoints, but NOT merely adjacent integers"
			// This means [1,2] and [3,4] are NOT merged because they don't share an endpoint
			// They only overlap if current.R >= next.L
			if current.R >= next.L {
				// Merge: extend the right endpoint
				if next.R > current.R {
					current.R = next.R
				}
			} else {
				// No overlap, add current and start new
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