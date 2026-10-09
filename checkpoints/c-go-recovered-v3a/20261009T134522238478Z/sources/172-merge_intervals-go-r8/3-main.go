package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	n, err := strconv.Atoi(scanner.Text())
	if err != nil || n < 0 || n > 200 {
		return
	}

	intervals := make([]struct{ L, R int64 }, n)
	for i := 0; i < n; i++ {
		var lStr, rStr string
		if !scanner.Scan() {
			return
		}
		lStr = scanner.Text()
		if !scanner.Scan() {
			return
		}
		rStr = scanner.Text()
		l, _ := strconv.Atoi(lStr)
		r, _ := strconv.Atoi(rStr)
		intervals[i].L = int64(l)
		intervals[i].R = int64(r)
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

	merged := make([]struct{ L, R int64 }, 0, n)
	current := intervals[0]
	for i := 1; i < n; i++ {
		next := intervals[i]
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

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}