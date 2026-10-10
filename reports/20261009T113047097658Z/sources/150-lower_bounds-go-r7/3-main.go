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
	tokens := []string{}

	var readToken func() string
	readToken = func() string {
		if len(tokens) == 0 {
			for scanner.Scan() {
				line := strings.TrimSpace(scanner.Text())
				if line != "" {
					tokens = append(tokens, strings.Fields(line)...)
				}
			}
		}
		if len(tokens) > 0 {
			val := tokens[0]
			tokens = tokens[1:]
			return val
		}
		return ""
	}

	// Read N and Q
	nStr := readToken()
	qStr := readToken()
	if nStr == "" || qStr == "" {
		return
	}
	n, _ := strconv.ParseInt(nStr, 10, 64)
	q, _ := strconv.ParseInt(qStr, 10, 64)

	// Read N integers
	arr := make([]int64, n)
	for i := int64(0); i < n; i++ {
		valStr := readToken()
		arr[i], _ = strconv.ParseInt(valStr, 10, 64)
	}

	// Process Q queries
	for i := int64(0); i < q; i++ {
		xStr := readToken()
		if xStr == "" {
			break
		}
		x, _ := strconv.ParseInt(xStr, 10, 64)
		idx := lowerBound(arr, x)
		fmt.Println(idx)
	}
}

func lowerBound(arr []int64, x int64) int {
	l, r := 0, len(arr)
	for l < r {
		mid := l + (r-l)/2
		if arr[mid] >= x {
			r = mid
		} else {
			l = mid + 1
		}
	}
	return l
}