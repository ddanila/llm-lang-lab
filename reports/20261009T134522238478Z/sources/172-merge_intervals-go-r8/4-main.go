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
	input := bufio.NewReader(os.Stdin)
	
	// Read all tokens
	tokens := []string{}
	line, err := input.ReadString('\n')
	if err == nil && len(line) > 0 {
		for _, token := range strings.Fields(line) {
			tokens = append(tokens, token)
		}
	}
	
	// Read remaining lines if any
	for {
		line, err = input.ReadString('\n')
		if err != nil || line == "" {
			break
		}
		for _, token := range strings.Fields(line) {
			tokens = append(tokens, token)
		}
	}

	if len(tokens) == 0 {
		fmt.Println(0)
		return
	}

	n, err := strconv.Atoi(tokens[0])
	if err != nil || n < 0 || n > 200 {
		fmt.Println(0)
		return
	}

	intervals := make([]struct{ L, R int64 }, n)
	idx := 1
	for i := 0; i < n; i++ {
		if idx >= len(tokens) {
			break
		}
		l, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		if idx >= len(tokens) {
			break
		}
		r, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		intervals[i].L = l
		intervals[i].R = r
	}

	if n == 0 {
		fmt.Println(0)
		return
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	merged := make([]struct{ L, R int64 }, 0, n)
	current := intervals[0]
	for i := 1; i < n; i++ {
		next := intervals[i]
		if next.L <= current.R {
			if next.R > current.R {
				current.R = next.R
			}
		} else {
			merged = append(merged, current)
			current = next
		}
	}
	merged = append(merged, current)

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}