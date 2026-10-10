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
		fmt.Println("0")
		return
	}
	n, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil {
		fmt.Println("0")
		return
	}

	intervals := make([]struct{ L, R int64 }, 0, n)
	for i := 0; i < n; i++ {
		scanner.Scan()
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) < 2 {
			continue
		}
		l, _ := strconv.ParseInt(tokens[0], 10, 64)
		r, _ := strconv.ParseInt(tokens[1], 10, 64)
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