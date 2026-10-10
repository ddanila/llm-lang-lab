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

	var lines strings.Builder
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		lines.WriteString(line)
	}
	input := lines.String()

	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("0")
		return
	}

	n, err := strconv.Atoi(tokens[0])
	if err != nil || n < 0 {
		fmt.Println("0")
		return
	}

	intervals := make([]struct{ L, R int64 }, 0)
	idx := 1
	for i := 0; i < n && idx+1 <= len(tokens); i++ {
		l, err := strconv.Atoi(tokens[idx])
		if err != nil {
			continue
		}
		r, err := strconv.Atoi(tokens[idx+1])
		if err != nil {
			continue
		}
		intervals = append(intervals, struct{ L, R int64 }{int64(l), int64(r)})
		idx += 2
	}

	if len(intervals) == 0 {
		fmt.Println("0")
		return
	}

	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i].L != intervals[j].L {
			return intervals[i].L < intervals[j].L
		}
		return intervals[i].R < intervals[j].R
	})

	var merged []struct{ L, R int64 }
	for _, interval := range intervals {
		if len(merged) == 0 {
			merged = append(merged, interval)
			continue
		}
		last := &merged[len(merged)-1]
		if interval.L <= last.R {
			if interval.R > last.R {
				last.R = interval.R
			}
		} else {
			merged = append(merged, interval)
		}
	}

	fmt.Println(len(merged))
	for _, m := range merged {
		fmt.Printf("%d %d\n", m.L, m.R)
	}
}