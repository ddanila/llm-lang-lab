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
	
	// Handle empty input case (though spec says N 0..200, so likely has at least one token)
	line = strings.TrimSpace(line)
	if line == "" {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(line)
	if err != nil {
		// Try reading more tokens if the first line is not a valid integer
		tokens := strings.Fields(line)
		if len(tokens) > 0 {
			n, err = strconv.Atoi(tokens[0])
			if err != nil {
				fmt.Println("0")
				return
			}
		} else {
			fmt.Println("0")
			return
		}
	}
	
	var intervals []struct {
		L, R int64
	}
	
	for i := 0; i < n; i++ {
		tokens, _ := reader.ReadString('\n')
		tokens = strings.TrimSpace(tokens)
		
		if tokens == "" && len(intervals) < n {
			// Try reading again if line is empty but we still need intervals
			continue
		}
		
		tokenList := strings.Fields(tokens)
		if len(tokenList) >= 2 {
			l, _ := strconv.ParseInt(tokenList[0], 10, 64)
			r, _ := strconv.ParseInt(tokenList[1], 10, 64)
			intervals = append(intervals, struct{ L, R int64 }{l, r})
		} else if len(tokenList) == 1 && i < n {
			// This shouldn't happen based on spec (pairs of integers)
			// but handle gracefully
			continue
		}
	}
	
	if n == 0 || len(intervals) == 0 {
		fmt.Println("0")
		return
	}
	
	// Sort intervals by L, then by R
	for i := 1; i < len(intervals); i++ {
		for j := 0; j < len(intervals)-i; j++ {
			if intervals[j].L > intervals[j+1].L || 
			   (intervals[j].L == intervals[j+1].L && intervals[j].R > intervals[j+1].R) {
				intervals[j], intervals[j+1] = intervals[j+1], intervals[j]
			}
		}
	}
	
	// Merge intervals
	var merged []struct {
		L, R int64
	}
	
	if len(intervals) > 0 {
		current := intervals[0]
		for i := 1; i < len(intervals); i++ {
			next := intervals[i]
			// Overlap condition: next.L <= current.R (shared endpoints count as overlap)
			if next.L <= current.R {
				// Merge: extend current R if needed
				if next.R > current.R {
					current.R = next.R
				}
			} else {
				// No overlap, add current and start new
				merged = append(merged, current)
				current = next
			}
		}
		merged = append(merged, current)
	}
	
	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}