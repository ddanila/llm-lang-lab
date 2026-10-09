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

	if !scanner.Scan() {
		return
	}
	tokens := strings.Split(string(scanner.Bytes()), " ")
	
	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		return
	}
	q, err := strconv.Atoi(tokens[1])
	if err != nil {
		return
	}

	arr := make([]int64, n)
	for i := 0; i < n; i++ {
		arr[i] = int64(0) // placeholder
	}
	
	idx := 2
	for i := 0; i < n && idx < len(tokens); i++ {
		val, _ := strconv.Atoi(tokens[idx])
		arr[i] = int64(val)
		idx++
	}

	for i := 0; i < q && idx < len(tokens); i++ {
		queryVal, _ := strconv.Atoi(tokens[idx])
		idx++

		result := findLowerBound(arr, int64(queryVal))
		fmt.Println(result)
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