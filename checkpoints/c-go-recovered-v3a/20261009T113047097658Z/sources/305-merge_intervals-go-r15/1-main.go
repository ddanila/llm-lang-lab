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
	reader := bufio.NewReader(os.Stdin)
	
	// Read N
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	// Trim and parse N
	line = strings.TrimSpace(line)
	if line == "" {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(line)
	if err != nil {
		// If the first non-empty token is not a valid integer for N, try reading tokens one by one
		tokens := strings.Fields(line)
		if len(tokens) > 0 {
			n, err = strconv.Atoi(tokens[0])
			if err != nil {
				return
			}
		} else {
			return
		}
	}
	
	var intervals []struct {
		L, R int64
	}
	
	count := 0
	for count < n {
		line, err = reader.ReadString('\n')
		if err != nil && len(line) == 0 {
			break
		}
		
		tokens := strings.Fields(line)
		for _, token := range tokens {
			l, _ := strconv.ParseInt(token, 10, 64)
			r, _ := strconv.ParseInt(token, 10, 64)
			intervals = append(intervals, struct{ L, R int64 }{L: l, R: r})
			count++
		}
	}
	
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	// Sort intervals by L, then by R
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})
	
	// Merge intervals
	var merged []struct {
		L, R int64
	}
	
	if len(intervals) > 0 {
		current := intervals[0]
		
		for i := 1; i < len(intervals); i++ {
			next := intervals[i]
			
			// Check if intervals overlap (including shared endpoints)
			if next.L <= current.R {
				// Merge: extend the current interval's R if needed
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
	}
	
	fmt.Printf("%d\n", len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}