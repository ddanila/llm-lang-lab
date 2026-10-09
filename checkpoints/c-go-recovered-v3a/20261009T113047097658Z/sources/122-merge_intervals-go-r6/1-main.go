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
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields := strings.Fields(line)
	if len(fields) == 0 {
		fmt.Println("0")
		return
	}
	n, err := strconv.Atoi(fields[0])
	if err != nil {
		return
	}

	var intervals []struct {
		L, R int64
	}

	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && line != "" {
			break
		}
		fields = strings.Fields(line)
		if len(fields) >= 2 {
			l, _ := strconv.Atoi(fields[0])
			r, _ := strconv.Atoi(fields[1])
			intervals = append(intervals, struct{ L, R int64 }{int64(l), int64(r)})
		}
	}

	if n == 0 {
		fmt.Println("0")
		return
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	merged := []struct {
		L, R int64
	}{intervals[0]}

	for i := 1; i < n; i++ {
		curr := &merged[len(merged)-1]
		next := &intervals[i]
		if next.L <= curr.R { // overlap or shared endpoint
			if next.R > curr.R {
				curr.R = next.R
			}
		} else {
			merged = append(merged, struct{ L, R int64 }{next.L, next.R})
		}
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}