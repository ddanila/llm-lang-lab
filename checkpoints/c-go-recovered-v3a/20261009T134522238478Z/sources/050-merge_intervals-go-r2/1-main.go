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
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	// Parse N from the first line (might have whitespace)
	input = strings.TrimSpace(input)
	if input == "" {
		fmt.Println("0")
		return
	}

	n, err := strconv.Atoi(input)
	if err != nil {
		// If parsing fails, try to extract number from full input
		tokens := strings.Fields(input)
		if len(tokens) > 0 {
			n, _ = strconv.Atoi(tokens[0])
		} else {
			fmt.Println("0")
			return
		}
	}

	intervals := make([]struct{ L, R int64 }, n)

	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		tokens := strings.Fields(line)
		if len(tokens) >= 2 {
			l, _ := strconv.Atoi64(tokens[0])
			r, _ := strconv.Atoi64(tokens[1])
			intervals[i] = struct{ L, R int64 }{int64(l), int64(r)}
		}
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	// Sort by L, then by R
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	// Merge intervals
	var merged []struct{ L, R int64 }
	if len(intervals) > 0 {
		current := intervals[0]
		for i := 1; i < len(intervals); i++ {
			next := intervals[i]
			// Check if they overlap (including shared endpoints)
			if next.L <= current.R {
				// Merge: extend the right endpoint if needed
				if next.R > current.R {
					current.R = next.R
				}
			} else {
				// No overlap, save current and start new
				merged = append(merged, current)
				current = next
			}
		}
		merged = append(merged, current)
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}