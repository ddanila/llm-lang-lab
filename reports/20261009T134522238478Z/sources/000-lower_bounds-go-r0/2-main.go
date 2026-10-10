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

	var input []string
	line, _ := reader.ReadString('\n')
	if line != "" {
		input = append(input, strings.Fields(line)...)
	}
	for {
		line, err := reader.ReadString('\n')
		if err != nil || line == "" {
			break
		}
		input = append(input, strings.Fields(line)...)
	}

	if len(input) < 2 {
		return
	}

	n, _ := strconv.Atoi(input[0])
	q, _ := strconv.Atoi(input[1])

	var arr []int64
	for i := 0; i < n; i++ {
		val, _ := strconv.Atoi(input[i+2])
		arr = append(arr, int64(val))
	}

	if q > 0 && len(input) > n+2 {
		for i := n + 2; i < len(input); i++ {
			x, _ := strconv.Atoi(input[i])
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