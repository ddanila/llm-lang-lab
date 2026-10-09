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
	fields := strings.Fields(input)
	if len(fields) < 2 {
		return
	}

	n, err := strconv.Atoi(fields[0])
	if err != nil {
		return
	}
	q, err := strconv.Atoi(fields[1])
	if err != nil {
		return
	}

	if n == 0 && q == 0 {
		return
	}

	var a []int64
	for i := 0; i < n; i++ {
		a = append(a, 0) // placeholder
	}

	idx := 2
	for i := 0; i < n; i++ {
		if idx >= len(fields) {
			break
		}
		val, _ := strconv.ParseInt(fields[idx], 10, 64)
		a[i] = val
		idx++
	}

	var queries []int64
	for i := 0; i < q; i++ {
		if idx >= len(fields) {
			break
		}
		val, _ := strconv.ParseInt(fields[idx], 10, 64)
		queries = append(queries, val)
		idx++
	}

	for _, x := range queries {
		result := binarySearch(a, x)
		fmt.Println(result)
	}
}

func binarySearch(arr []int64, x int64) int {
	left, right := 0, len(arr)
	for left < right {
		mid := left + (right-left)/2
		if arr[mid] >= x {
			right = mid
		} else {
			left = mid + 1
		}
	}
	return left
}