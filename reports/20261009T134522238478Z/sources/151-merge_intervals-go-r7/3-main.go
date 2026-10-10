package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	n, err := strconv.Atoi(scanner.Text())
	if err != nil {
		fmt.Fprintln(os.Stderr, "error parsing N:", err)
		return
	}

	intervals := make([][2]int, 0, n)
	for i := 0; i < n; i++ {
		var l, r int
		if !scanner.Scan() {
			break
		}
		l, err = strconv.Atoi(scanner.Text())
		if err != nil {
			fmt.Fprintln(os.Stderr, "error parsing L:", err)
			return
		}
		if !scanner.Scan() {
			break
		}
		r, err = strconv.Atoi(scanner.Text())
		if err != nil {
			fmt.Fprintln(os.Stderr, "error parsing R:", err)
			return
		}
		intervals = append(intervals, [2]int{l, r})
	}

	if n == 0 {
		fmt.Println(0)
		return
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] != intervals[j][0] {
			return intervals[i][0] < intervals[j][0]
		}
		return intervals[i][1] < intervals[j][1]
	})

	var merged []struct {
		l, r int
	}
	if len(intervals) > 0 {
		current := intervals[0]
		for i := 1; i < len(intervals); i++ {
			next := intervals[i]
			if next[0] <= current[1] {
				// Overlap or shared endpoint -> merge
				if next[1] > current[1] {
					current[1] = next[1]
				}
			} else {
				merged = append(merged, struct{ l, r int }{l: current[0], r: current[1]})
				current = next
			}
		}
		merged = append(merged, struct{ l, r int }{l: current[0], r: current[1]})
	}

	fmt.Println(len(merged))
	for _, iv := range merged {
		fmt.Printf("%d %d\n", iv.l, iv.r)
	}
}