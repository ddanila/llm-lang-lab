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
	if !scanner.Scan() {
		return
	}
	input := strings.TrimSpace(scanner.Text())
	if input == "" {
		fmt.Println("0")
		return
	}

	// Parse N
	n, err := strconv.Atoi(strings.Split(input, "\n")[0])
	if err != nil {
		// Try to find the number in the first line
		parts := strings.Fields(input)
		if len(parts) == 0 {
			fmt.Println("0")
			return
		}
		n = parts[0]
		if nStr, ok := n.(string); ok {
			// This shouldn't happen with Atoi
		} else if _, ok := interface{}(n).(int); !ok {
			fmt.Println("0")
			return
		}
	}

	// Actually, let's re-parse properly
	lines := strings.Split(input, "\n")
	if len(lines) == 0 {
		fmt.Println("0")
		return
	}
	
	var nInt int
	if _, err := fmt.Sscanf(lines[0], "%d", &nInt); err != nil {
		nInt = 0
	}

	intervals := make([][2]int, 0)
	idx := 1
	for i := 0; i < nInt && idx < len(lines); i++ {
		line := lines[idx]
		idx++
		if line == "" {
			continue
		}
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
		fmt.Println("0")
		return
	}

	merged := make([][2]int, 0)
	currentStart := intervals[0][0]
	currentEnd := intervals[0][1]

	for i := 1; i < len(intervals); i++ {
		if intervals[i][0] <= currentEnd {
			// Overlapping or sharing endpoint
			if intervals[i][1] > currentEnd {
				currentEnd = intervals[i][1]
			}
		} else {
			merged = append(merged, [2]int{currentStart, currentEnd})
			currentStart = intervals[i][0]
			currentEnd = intervals[i][1]
		}
	}
	merged = append(merged, [2]int{currentStart, currentEnd})

	fmt.Println(len(merged))
	for _, interval := range merged {
		fmt.Printf("%d %d\n", interval[0], interval[1])
	}
}