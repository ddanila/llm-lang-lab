package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	if !scanner.Scan() {
		return
	}
	tokens := scanner.Bytes()
	n, err := strconv.Atoi(string(tokens[0]))
	if err != nil {
		return
	}
	q, err := strconv.Atoi(string(tokens[1]))
	if err != nil {
		return
	}

	arr := make([]int64, n)
	idx := 0
	for i := 0; i < n; i++ {
		if idx+1 >= len(tokens) {
			break
		}
		val, _ := strconv.Atoi(string(tokens[idx+1]))
		arr[i] = int64(val)
		idx += 2
	}

	if q > 0 && idx+1 < len(tokens) {
		for i := 0; i < q; i++ {
			if idx+1 >= len(tokens) {
				break
			}
			queryVal, _ := strconv.Atoi(string(tokens[idx+1]))
			idx += 2

			result := findLowerBound(arr, int64(queryVal))
			fmt.Println(result)
		}
	}
}

func findLowerBound(arr []int64, target int64) int {
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