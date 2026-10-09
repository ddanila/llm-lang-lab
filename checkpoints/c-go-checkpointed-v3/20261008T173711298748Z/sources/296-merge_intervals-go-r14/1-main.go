package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	line := strings.TrimSpace(scanner.Text())
	if line == "" {
		fmt.Println(0)
		return
	}
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}

	var intervals [200][2]int64
	count := 0

	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		fields := strings.Fields(scanner.Text())
		if len(fields) >= 2 {
			l, _ := strconv.ParseInt(fields[0], 10, 64)
			r, _ := strconv.ParseInt(fields[1], 10, 64)
			intervals[count] = [2]int64{l, r}
			count++
		}
	}

	if count == 0 {
		fmt.Println(0)
		return
	}

	// Sort intervals by L ascending
	for i := 0; i < count-1; i++ {
		for j := i + 1; j < count; j++ {
			if intervals[i][0] > intervals[j][0] || (intervals[i][0] == intervals[j][0] && intervals[i][1] > intervals[j][1]) {
				intervals[i], intervals[j] = intervals[j], intervals[i]
			}
		}
	}

	merged := 0
	start := intervals[0][0]
	end := intervals[0][1]

	for i := 1; i < count; i++ {
		if intervals[i][0] <= end {
			if intervals[i][1] > end {
				end = intervals[i][1]
			}
		} else {
			merged++
			start = intervals[i][0]
			end = intervals[i][1]
		}
	}

	merged++ // Add the last interval
	fmt.Println(merged)

	for i := 0; i < merged; i++ {
		fmt.Printf("%d %d\n", start, end)
	}
}