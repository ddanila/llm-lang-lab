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
	n, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil || n < 0 || n > 200 {
		return
	}

	intervals := make([]struct{ L, R int64 }, 0, n)
	tokenCount := 0
	for i := 0; i < n; i++ {
		for tokenCount < 2*(i+1) {
			if !scanner.Scan() {
				return
			}
			token := strings.TrimSpace(scanner.Text())
			if token != "" {
				val, _ := strconv.ParseInt(token, 10, 64)
				if i%2 == 0 {
					intervals[i/2].L = val
				} else {
					idx := (i - 1) / 2
					intervals[idx].R = val
				}
			}
			tokenCount++
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