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
	var n int
	
	if !scanner.Scan() {
		return
	}
	
	line := scanner.Text()
	fields := strings.Fields(line)
	if len(fields) == 0 {
		fmt.Println(0)
		return
	}
	
	n, _ = strconv.Atoi(fields[0])
	
	intervals := make([]struct{ L, R int }, n)
	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		fields = strings.Fields(scanner.Text())
		intervals[i].L, _ = strconv.Atoi(fields[0])
		intervals[i].R, _ = strconv.Atoi(fields[1])
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