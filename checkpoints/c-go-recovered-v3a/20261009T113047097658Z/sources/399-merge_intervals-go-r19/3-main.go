package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	var n int
	if _, err := fmt.Fscan(reader, &n); err != nil {
		return
	}

	intervals := make([]struct{ L, R int }, n)
	for i := 0; i < n; i++ {
		if _, err := fmt.Fscanf(reader, "%d %d", &intervals[i].L, &intervals[i].R); err != nil {
			return
		}
	}

	if n == 0 {
		fmt.Println(0)
		return
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	var merged []struct{ L, R int }
	start := intervals[0].L
	end := intervals[0].R

	for i := 1; i < n; i++ {
		if intervals[i].L <= end {
			if intervals[i].R > end {
				end = intervals[i].R
			}
		} else {
			merged = append(merged, struct{ L, R int }{start, end})
			start = intervals[i].L
			end = intervals[i].R
		}
	}
	merged = append(merged, struct{ L, R int }{start, end})

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}