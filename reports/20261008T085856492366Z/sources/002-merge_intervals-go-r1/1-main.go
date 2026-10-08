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
		// Try reading more tokens if the first line is not a single number
		tokens := strings.Fields(line)
		if len(tokens) == 0 {
			fmt.Println("0")
			return
		}
		n, err = strconv.Atoi(tokens[0])
		if err != nil {
			return
		}
	}

	intervals := make([]struct{ L, R int64 }, n)
	for i := 0; i < n; i++ {
		line, _ = reader.ReadString('\n')
		tokens := strings.Fields(line)
		if len(tokens) >= 2 {
			l, _ := strconv.ParseInt(tokens[0], 10, 64)
			r, _ := strconv.ParseInt(tokens[1], 10, 64)
			intervals[i] = struct{ L, R int64 }{L: l, R: r}
		} else {
			// Read more lines until we have enough tokens
			for len(tokens) < 2 {
				line, _ = reader.ReadString('\n')
				tokens = append(tokens, strings.Fields(line)...)
			}
			l, _ := strconv.ParseInt(tokens[0], 10, 64)
			r, _ := strconv.ParseInt(tokens[1], 10, 64)
			intervals[i] = struct{ L, R int64 }{L: l, R: r}
		}
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	// Sort by L ascending, then by R ascending
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	merged := make([]struct{ L, R int64 }, 0, n)
	for i := 0; i < n; i++ {
		if len(merged) == 0 {
			merged = append(merged, intervals[i])
		} else {
			last := merged[len(merged)-1]
			// Merge if overlapping or sharing an endpoint: last.R >= intervals[i].L
			if last.R >= intervals[i].L {
				merged[len(merged)-1].R = max(last.R, intervals[i].R)
			} else {
				merged = append(merged, intervals[i])
			}
		}
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}

func max(a, b int64) int64 {
	if a > b {
		return a
	}
	return b
}