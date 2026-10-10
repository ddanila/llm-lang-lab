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
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println(0)
		return
	}

	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		fmt.Println(0)
		return
	}

	intervals := make([][2]int, 0)
	idx := 1
	for i := 0; i < n; i++ {
		if idx >= len(tokens) {
			break
		}
		l, err := strconv.Atoi(tokens[idx])
		if err != nil {
			continue
		}
		idx++
		r, err := strconv.Atoi(tokens[idx])
		if err != nil {
			continue
		}
		intervals = append(intervals, [2]int{l, r})
		idx++
	}

	sort.Slice(intervals, func(i, j int) bool {
		return intervals[i][0] < intervals[j][0]
	})

	if len(intervals) == 0 {
		fmt.Println(0)
		return
	}

	merged := make([][2]int, 0)
	merged = append(merged, intervals[0])

	for i := 1; i < len(intervals); i++ {
		currentStart, currentEnd := merged[len(merged)-1][0], merged[len(merged)-1][1]
		nextStart, nextEnd := intervals[i][0], intervals[i][1]

		if nextStart <= currentEnd {
			newEnd := currentEnd
			if nextEnd > newEnd {
				newEnd = nextEnd
			}
			merged[len(merged)-1] = [2]int{currentStart, newEnd}
		} else {
			merged = append(merged, intervals[i])
		}
	}

	fmt.Println(len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}