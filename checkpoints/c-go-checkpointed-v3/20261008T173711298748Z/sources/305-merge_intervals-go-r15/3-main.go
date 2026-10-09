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
	
	// Read all input from stdin
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	
	// Continue reading if there are more tokens
	for len(tokens) == 0 || tokens[len(tokens)-1] == "" {
		line, _ := reader.ReadString('\n')
		tokens = append(tokens, strings.Fields(line)...)
	}
	
	if len(tokens) == 0 {
		fmt.Println("0")
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	
	var intervals []struct {
		L, R int64
	}
	
	tokenIdx := 1
	for i := 0; i < n && tokenIdx+1 < len(tokens); i++ {
		l, _ := strconv.ParseInt(tokens[tokenIdx], 10, 64)
		r, _ := strconv.ParseInt(tokens[tokenIdx+1], 10, 64)
		intervals = append(intervals, struct{ L, R int64 }{L: l, R: r})
		tokenIdx += 2
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
	
	// Merge intervals - overlap when next.L <= current.R (closed intervals)
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