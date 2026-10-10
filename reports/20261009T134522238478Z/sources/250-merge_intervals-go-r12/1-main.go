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
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	if input == "" {
		fmt.Println("0")
		return
	}
	
	n, err := strconv.Atoi(input)
	if err != nil {
		fmt.Println(0)
		return
	}
	
	if n == 0 {
		fmt.Println("0")
		return
	}
	
	// Read N pairs
	intervals := make([][2]int, n)
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.Atoi(parts[0])
			r, _ := strconv.Atoi(parts[1])
			intervals[i] = [2]int{l, r}
		}
	}
	
	// Sort by start time, then by end time
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})
	
	// Merge intervals
	if len(intervals) == 0 {
		fmt.Println("0")
		return
	}
	
	merged := make([][2]int, 0, len(intervals))
	current := intervals[0]
	
	for i := 1; i < len(intervals); i++ {
		next := intervals[i]
		
		// Check if they overlap (including shared endpoints)
		if next[0] <= current[1] {
			// Merge them
			current[1] = max(current[1], next[1])
		} else {
			// No overlap, add current and move to next
			merged = append(merged, current)
			current = next
		}
	}
	
	// Add the last interval
	merged = append(merged, current)
	
	// Output
	fmt.Printf("%d\n", len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}