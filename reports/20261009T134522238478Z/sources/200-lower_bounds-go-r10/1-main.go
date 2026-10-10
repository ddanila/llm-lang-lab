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
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		return
	}

	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])

	var arr []int64
	idx := 2
	for i := 0; i < N; i++ {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		arr = append(arr, val)
		idx++
	}

	if Q > 0 {
		queryTokens := make([]string, 0, Q)
		for i := idx; i < len(tokens); i++ {
			queryTokens = append(queryTokens, tokens[i])
		}

		for _, qStr := range queryTokens {
			x, _ := strconv.ParseInt(qStr, 10, 64)
			idx := lowerBound(arr, x)
			fmt.Println(idx)
		}
	}
}

func lowerBound(arr []int64, x int64) int {
	l, r := 0, len(arr)
	for l < r {
		m := (l + r) / 2
		if arr[m] >= x {
			r = m
		} else {
			l = m + 1
		}
	}
	return l
}