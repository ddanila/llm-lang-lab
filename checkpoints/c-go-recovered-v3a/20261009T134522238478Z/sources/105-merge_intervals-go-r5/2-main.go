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
	
	var n int
	if scanner.Scan() {
		n, _ = strconv.Atoi(strings.TrimSpace(scanner.Text()))
	}
	
	intervals := make([][2]int, 0, n)
	tokens := make([]string, 0)
	
	for len(tokens) < n*2 {
		line, err := scanner.ReadString('\n')
		if err != nil || len(line) == 0 {
			break
		}
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		for _, tok := range strings.Fields(line) {
			tokens = append(tokens, tok)
		}
	}
	
	for i := 0; i < len(tokens); i += 2 {
		l, _ := strconv.Atoi(tokens[i])
		r, _ := strconv.Atoi(tokens[i+1])
		intervals = append(intervals, [2]int{l, r})
	}
	
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})
	
	if n == 0 || len(intervals) == 0 {
		fmt.Println(0)
		return
	}
	
	merged := make([][2]int, 0)
	currentStart, currentEnd := intervals[0][0], intervals[0][1]
	
	for i := 1; i < len(intervals); i++ {
		nextStart, nextEnd := intervals[i][0], intervals[i][1]
		
		if nextStart <= currentEnd {
			if nextEnd > currentEnd {
				currentEnd = nextEnd
			}
		} else {
			merged = append(merged, [2]int{currentStart, currentEnd})
			currentStart, currentEnd = nextStart, nextEnd
		}
	}
	merged = append(merged, [2]int{currentStart, currentEnd})
	
	fmt.Printf("%d\n", len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}