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
	if _, err := fmt.Fscanf(reader, "%d", &n); err != nil {
		fmt.Fprintln(os.Stdout, "0")
		return
	}

	intervals := make([][2]int, 0, n)

	for i := 0; i < n; i++ {
		var l, r int
		if _, err := fmt.Fscan(reader, &l, &r); err != nil {
			fmt.Fprintln(os.Stdout, "0")
			return
		}
		intervals = append(intervals, [2]int{l, r})
	}

	if n == 0 {
		fmt.Fprintln(os.Stdout, "0")
		return
	}

	sort.Slice(intervals, func(i, j int) bool {
		return intervals[i][0] < intervals[j][0]
	})

	merged := make([][2]int, 0, n)
	if len(intervals) > 0 {
		merged = append(merged, intervals[0])
	}

	for i := 1; i < len(intervals); i++ {
		last := merged[len(merged)-1]
		curr := intervals[i]

		if curr[0] <= last[1] {
			newEnd := last[1]
			if curr[1] > newEnd {
				newEnd = curr[1]
			}
			merged[len(merged)-1] = [2]int{last[0], newEnd}
		} else {
			merged = append(merged, curr)
		}
	}

	fmt.Fprintln(os.Stdout, len(merged))
	for _, interval := range merged {
		fmt.Fprintf(os.Stdout, "%d %d\n", interval[0], interval[1])
	}
}