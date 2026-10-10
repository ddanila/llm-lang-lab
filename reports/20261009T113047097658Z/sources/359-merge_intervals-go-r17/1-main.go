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
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	nStr := strings.TrimSpace(scanner.Text())
	n, err := strconv.Atoi(nStr)
	if err != nil {
		return
	}

	var intervals []struct {
		L, R int64
	}
	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		line := strings.TrimSpace(scanner.Text())
		fields := strings.Fields(line)
		if len(fields) >= 2 {
			l, _ := strconv.ParseInt(fields[0], 10, 64)
			r, _ := strconv.ParseInt(fields[1], 10, 64)
			intervals = append(intervals, struct{ L, R int64 }{L: l, R: r})
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

	var merged []struct {
		L, R int64
	}
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