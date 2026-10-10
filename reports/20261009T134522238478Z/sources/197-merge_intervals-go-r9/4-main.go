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
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	intervals := make([][2]int64, 0, n)
	for i := 0; i < n; i++ {
		var lStr, rStr string
		if !scanner.Scan() {
			break
		}
		lStr = scanner.Text()
		if !scanner.Scan() {
			break
		}
		rStr = scanner.Text()
		
		l, err := strconv.ParseInt(lStr, 10, 64)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		r, err := strconv.ParseInt(rStr, 10, 64)
		if err != nil {
			fmt.Fprintln(os.Stderr, err)
			os.Exit(1)
		}
		intervals = append(intervals, [2]int64{l, r})
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})

	if len(intervals) == 0 {
		fmt.Println("0")
		return
	}

	var merged [][2]int64
	start := intervals[0][0]
	end := intervals[0][1]

	for i := 1; i < len(intervals); i++ {
		l, r := intervals[i][0], intervals[i][1]
		if l <= end { // Overlap including shared endpoints
			if r > end {
				end = r
			}
		} else {
			merged = append(merged, [2]int64{start, end})
			start = l
			end = r
		}
	}
	merged = append(merged, [2]int64{start, end})

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m[0], m[1])
	}
}