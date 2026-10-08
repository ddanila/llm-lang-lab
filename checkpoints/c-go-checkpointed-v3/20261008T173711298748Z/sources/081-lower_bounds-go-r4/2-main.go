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

	N, err := strconv.Atoi(tokens[0])
	if err != nil {
		return
	}

	Q, _ := strconv.Atoi(tokens[1])

	if N > len(tokens)-2 {
		N = len(tokens) - 2
	}

	arr := make([]int64, N)
	for i := 0; i < N; i++ {
		val, _ := strconv.ParseInt(tokens[2+i], 10, 64)
		arr[i] = val
	}

	queryIdx := 2 + N
	if queryIdx > len(tokens) {
		return
	}

	for qIdx := queryIdx; qIdx < len(tokens); qIdx++ {
		xStr := tokens[qIdx]
		x, _ := strconv.ParseInt(xStr, 10, 64)

		idx := lowerBound(arr, x)
		fmt.Println(idx)
	}
}

func lowerBound(arr []int64, target int64) int {
	left := 0
	right := len(arr)

	for left < right {
		mid := left + (right-left)/2
		if arr[mid] >= target {
			right = mid
		} else {
			left = mid + 1
		}
	}

	return left
}