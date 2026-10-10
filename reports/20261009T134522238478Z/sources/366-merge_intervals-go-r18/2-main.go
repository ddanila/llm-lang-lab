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
	var n int
	line, _ := reader.ReadString('\n')
	fmt.Sscanf(line, "%d", &n)

	// Read intervals
	intervals := make([]struct{ L, R int }, n)
	for i := 0; i < n; i++ {
		line, _ = reader.ReadString('\n')
		tokens := strings.Fields(line)
		if len(tokens) >= 2 {
			l, _ := strconv.Atoi(tokens[0])
			r, _ := strconv.Atoi(tokens[1])
			intervals[i] = struct{ L, R int }{l, r}
		}
	}

	if n == 0 {
		fmt.Println(0)
		return
	}

	// Sort by L, then by R
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	// Merge intervals
	var merged []struct{ L, R int }
	for _, interval := range intervals {
		if len(merged) == 0 {
			merged = append(merged, interval)
		} else {
			last := &merged[len(merged)-1]
			if interval.L <= last.R { // overlap or shared endpoint
				if interval.R > last.R {
					last.R = interval.R
				}
			} else {
				merged = append(merged, interval)
			}
		}
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}