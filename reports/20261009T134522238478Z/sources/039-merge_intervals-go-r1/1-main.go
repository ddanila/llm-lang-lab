package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		fmt.Println(0)
		return
	}
	
	n, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil {
		fmt.Println(0)
		return
	}
	
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	intervals := make([]struct{ L, R int64 }, n)
	for i := 0; i < n; i++ {
		scanner.Scan()
		tokens := strings.Fields(scanner.Text())
		if len(tokens) != 2 {
			continue
		}
		l, _ := strconv.ParseInt(tokens[0], 10, 64)
		r, _ := strconv.ParseInt(tokens[1], 10, 64)
		intervals[i] = struct{ L, R int64 }{L: l, R: r}
	}
	
	// Sort by L ascending, then by R ascending
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[j].L < intervals[i].L || (intervals[j].L == intervals[i].L && intervals[j].R < intervals[i].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	merged := make([]struct{ L, R int64 }, 0, n)
	if len(intervals) > 0 {
		currentL := intervals[0].L
		currentR := intervals[0].R
		
		for i := 1; i < n; i++ {
			nextL := intervals[i].L
			nextR := intervals[i].R
			
			if nextL <= currentR {
				// Overlapping or sharing an endpoint, merge
				if nextR > currentR {
					currentR = nextR
				}
			} else {
				// No overlap, push current and start new
				merged = append(merged, struct{ L, R int64 }{L: currentL, R: currentR})
				currentL = nextL
				currentR = nextR
			}
		}
		merged = append(merged, struct{ L, R int64 }{L: currentL, R: currentR})
	}
	
	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}