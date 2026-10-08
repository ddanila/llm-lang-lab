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

	var N int
	if s, _ := reader.ReadString('\n'); s != "" {
		s = strings.TrimSpace(s)
		if s != "" {
			n, _ := strconv.Atoi(s)
			N = n
		}
	}

	if N <= 0 {
		fmt.Println(0)
		return
	}

	intervals := make([][2]int, 0, N)
	for i := 0; i < N; i++ {
		line, _ := reader.ReadString('\n')
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			l, _ := strconv.Atoi(parts[0])
			r, _ := strconv.Atoi(parts[1])
			intervals = append(intervals, [2]int{l, r})
		}
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})

	if len(intervals) == 0 {
		fmt.Println(0)
		return
	}

	var merged [2]int = intervals[0]
	result := make([][2]int, 0)
	result = append(result, merged)

	for i := 1; i < len(intervals); i++ {
		currL, currR := intervals[i][0], intervals[i][1]
		lastR := merged[1]

		if currL <= lastR {
			if currR > lastR {
				merged[1] = currR
			}
		} else {
			result = append(result, intervals[i])
		}
	}

	fmt.Println(len(result))
	for _, interval := range result {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}