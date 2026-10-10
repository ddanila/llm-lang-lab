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
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	if input == "" {
		fmt.Println(0)
		return
	}
	n, err := strconv.Atoi(strings.TrimSpace(input))
	if err != nil {
		return
	}
	
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	intervals := make([]struct {
		L, R int64
	}, n)
	
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.Atoi(parts[0])
			r, _ := strconv.Atoi(parts[1])
			intervals[i] = struct {
				L, R int64
			}{int64(l), int64(r)}
		}
	}
	
	// Sort by L ascending
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			if intervals[j].L > intervals[j+1].L {
				intervals[j], intervals[j+1] = intervals[j+1], intervals[j]
			}
		}
	}
	
	// Merge overlapping intervals (including shared endpoints)
	merged := make([]struct {
		L, R int64
	}, 0)
	if n > 0 {
		currentL := intervals[0].L
		currentR := intervals[0].R
		
		for i := 1; i < n; i++ {
			nextL := intervals[i].L
			nextR := intervals[i].R
			
			// Check if they overlap or share an endpoint
			if nextL <= currentR {
				// Merge: extend the right boundary if needed
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
		// Push the last one
		merged = append(merged, struct {
			L, R int64
		}{currentL, currentR})
	}
	
	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}