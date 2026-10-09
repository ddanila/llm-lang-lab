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
	if !scanner.Scan() {
		fmt.Println(0)
		return
	}
	
	n, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil || n < 0 || n > 200 {
		fmt.Println(0)
		return
	}
	
	intervals := make([]struct{ L, R int64 }, 0, n)
	
	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		tokens := strings.Fields(scanner.Text())
		if len(tokens) < 2 {
			break
		}
		
		l, err1 := strconv.ParseInt(tokens[0], 10, 64)
		r, err2 := strconv.ParseInt(tokens[1], 10, 64)
		if err1 != nil || err2 != nil {
			break
		}
		
		intervals = append(intervals, struct{ L, R int64 }{l, r})
	}
	
	if len(intervals) == 0 {
		fmt.Println(0)
		return
	}
	
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})
	
	merged := []struct{ L, R int64 }{}
	currentL := intervals[0].L
	currentR := intervals[0].R
	
	for i := 1; i < len(intervals); i++ {
		next := &intervals[i]
		
		if next.L <= currentR {
			if next.R > currentR {
				currentR = next.R
			}
		} else {
			merged = append(merged, struct{ L, R int64 }{currentL, currentR})
			currentL = next.L
			currentR = next.R
		}
	}
	
	merged = append(merged, struct{ L, R int64 }{currentL, currentR})
	
	fmt.Println(len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval.L, interval.R)
	}
}