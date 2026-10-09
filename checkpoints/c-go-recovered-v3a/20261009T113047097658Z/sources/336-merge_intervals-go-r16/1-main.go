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
	input, err := reader.ReadString('\n')
	if err != nil {
		os.Exit(1)
	}
	
	input = strings.TrimSpace(input)
	if input == "" {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(strings.Split(input, "\n")[0])
	if err != nil {
		os.Exit(1)
	}
	
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	// Read N pairs
	intervals := make([]struct {
		L, R int64
	}, n)
	
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err.Error() != "EOF" {
			os.Exit(1)
		}
		
		parts := strings.Fields(strings.TrimSpace(line))
		l, _ := strconv.ParseInt(parts[0], 10, 64)
		r, _ := strconv.ParseInt(parts[1], 10, 64)
		
		intervals[i] = struct {
			L, R int64
		}{l, r}
	}
	
	// Sort intervals by L, then by R
	for i := 0; i < n-1; i++ {
		for j := i + 1; j < n; j++ {
			if intervals[j].L < intervals[i].L || 
			   (intervals[j].L == intervals[i].L && intervals[j].R < intervals[i].R) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}
	
	// Merge intervals
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	var merged []struct {
		L, R int64
	}
	
	currentL := intervals[0].L
	currentR := intervals[0].R
	
	for i := 1; i < n; i++ {
		nextL := intervals[i].L
		nextR := intervals[i].R
		
		// Merge if overlapping (including shared endpoints)
		if nextL <= currentR {
			// Overlap or touch at endpoint, merge
			if nextR > currentR {
				currentR = nextR
			}
		} else {
			// No overlap, push current and start new
			merged = append(merged, struct {
				L, R int64
			}{currentL, currentR})
			currentL = nextL
			currentR = nextR
		}
	}
	
	// Push the last interval
	merged = append(merged, struct {
		L, R int64
	}{currentL, currentR})
	
	fmt.Printf("%d\n", len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}