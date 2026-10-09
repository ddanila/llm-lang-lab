package main

import (
	"bufio"
	"fmt"
	"os"
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
		// Try to parse from remaining tokens if first line is not just N
		tokens := strings.Fields(line)
		if len(tokens) > 0 {
			n, _ = strconv.Atoi(tokens[0])
		} else {
			fmt.Println("0")
			return
		}
	}
	
	intervals := make([]struct{ L, R int64 }, n)
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err.Error() != "EOF" {
			break
		}
		tokens := strings.Fields(line)
		if len(tokens) >= 2 {
			l, _ := strconv.ParseInt(tokens[0], 10, 64)
			r, _ := strconv.ParseInt(tokens[1], 10, 64)
			intervals[i] = struct{ L, R int64 }{L: l, R: r}
		}
	}
	
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	// Sort intervals by L, then by R
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[i].L > intervals[j].L || (intervals[i].L == intervals[j].L && intervals[i].R > intervals[j].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	// Merge intervals
	var merged []struct{ L, R int64 }
	if n > 0 {
		merged = append(merged, intervals[0])
		for i := 1; i < n; i++ {
			last := merged[len(merged)-1]
			curr := intervals[i]
			// Merge if they overlap (including shared endpoints)
			if curr.L <= last.R {
				merged[len(merged)-1].R = max(last.R, curr.R)
			} else {
				merged = append(merged, curr)
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