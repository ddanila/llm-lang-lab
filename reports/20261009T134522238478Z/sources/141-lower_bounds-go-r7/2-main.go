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
	
	// Read all input from stdin
	var input strings.Builder
	for {
		ch, _, err := reader.ReadRune()
		if err != nil {
			break
		}
		input.WriteRune(ch)
	}
	inputStr := input.String()
	
	fields := strings.Fields(inputStr)
	if len(fields) == 0 {
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

	var a []int64
	for i := 0; i < n; i++ {
		if len(fields) <= 2+i {
			break
		}
		val, _ := strconv.ParseInt(fields[2+i], 10, 64)
		a = append(a, val)
	}

	var queries []int64
	for i := 0; i < q; i++ {
		if len(fields) <= 2+n+i {
			break
		}
		val, _ := strconv.ParseInt(fields[2+n+i], 10, 64)
		queries = append(queries, val)
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