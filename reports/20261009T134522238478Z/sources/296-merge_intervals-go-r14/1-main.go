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
	
	input, _ := reader.ReadString('\n')
	parts := strings.Fields(input)
	if len(parts) == 0 {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(parts[0])
	if err != nil {
		fmt.Println("0")
		return
	}
	
	intervals := make([]struct {
		L int64
		R int64
	}, n)
	
	idx := 1
	for i := 0; i < n; i++ {
		if idx >= len(parts) {
			break
		}
		l, _ := strconv.Atoi(parts[idx])
		r, _ := strconv.Atoi(parts[idx+1])
		intervals[i] = struct {
			L int64
			R int64
		}{int64(l), int64(r)}
		idx += 2
	}
	
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	// Sort intervals by L ascending, then by R ascending for ties
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[j].L < intervals[i].L || (intervals[j].L == intervals[i].L && intervals[j].R < intervals[i].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	// Merge intervals
	var merged []struct {
		L int64
		R int64
	}
	
	current := intervals[0]
	for i := 1; i < n; i++ {
		next := intervals[i]
		if next.L <= current.R {
			// Overlap or share endpoint, merge
			if next.R > current.R {
				current.R = next.R
			}
		} else {
			// No overlap, push current and start new
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