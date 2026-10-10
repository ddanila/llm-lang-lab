package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	input, _ := reader.ReadString('\n')
	parts := strings.Fields(input)

	if len(parts) < 2 {
		return
	}

	n, _ := strconv.Atoi(parts[0])
	q, _ := strconv.Atoi(parts[1])

	var arr []int64
	for i := 0; i < n; i++ {
		val, _ := strconv.Atoi(parts[i+2])
		arr = append(arr, int64(val))
	}

	if q > 0 {
		queryStart := len(parts) + 2
		for i := queryStart; i < len(parts); i++ {
			x, _ := strconv.Atoi(parts[i])
			idx := lowerBound(arr, int64(x))
			fmt.Println(idx)
		}
	}
}

func lowerBound(arr []int64, x int64) int {
	l, r := 0, len(arr)
	for l < r {
		m := l + (r-l)/2
		if arr[m] >= x {
			r = m
		} else {
			l = m + 1
		}
	}
	return l
}