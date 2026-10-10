package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	var n int
	if s, err := reader.ReadString('\n'); err == nil {
		n, _ = strconv.Atoi(s)
	}
	
	intervals := make([][2]int, 0, n)
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		tokens := splitWhitespace(line)
		if len(tokens) >= 2 {
			l, _ := strconv.Atoi(tokens[0])
			r, _ := strconv.Atoi(tokens[1])
			intervals = append(intervals, [2]int{l, r})
		}
	}
	
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})
	
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	merged := make([][2]int, 0)
	currentStart, currentEnd := intervals[0][0], intervals[0][1]
	
	for i := 1; i < n; i++ {
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

func splitWhitespace(s string) []string {
	var tokens []string
	start := 0
	for i := 0; i < len(s); i++ {
		if s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' {
			if start < i {
				tokens = append(tokens, s[start:i])
			}
			start = i + 1
		}
	}
	if start < len(s) {
		tokens = append(tokens, s[start:])
	}
	return tokens
}