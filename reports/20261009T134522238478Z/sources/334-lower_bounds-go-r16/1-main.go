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
	
	if len(tokens) < 2 {
		return
	}
	
	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		return
	}
	
	q, err := strconv.Atoi(tokens[1])
	if err != nil {
		return
	}
	
	var arr []int64
	for i := 2; i < len(tokens) && len(arr) < n; i++ {
		val, _ := strconv.ParseInt(tokens[i], 10, 64)
		arr = append(arr, val)
	}
	
	// Read remaining tokens for queries if needed
	allInput, _ := reader.ReadString('\n')
	allTokens := strings.Fields(allInput)
	
	queryTokens := allTokens[len(tokens)-len(allTokens)+len(arr):]
	if len(queryTokens) > 0 {
		for i := range queryTokens {
			// Combine with next line if needed
		}
	}
	
	// Actually, let's re-read properly
	tokens = strings.Fields(input + allInput)
	
	idx := 2
	arr = make([]int64, n)
	for i := 0; i < n && idx < len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		arr[i] = val
		idx++
	}
	
	// Read queries
	var queries []int64
	for idx < len(tokens) {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		queries = append(queries, val)
		idx++
	}
	
	if q == 0 {
		return
	}
	
	// Binary search for each query
	for _, x := range queries[:q] {
		l, r := 0, n-1
		result := -1
		for l <= r {
			mid := (l + r) / 2
			if arr[mid] >= x {
				result = mid
				r = mid - 1
			} else {
				l = mid + 1
			}
		}
		
		if result == -1 {
			fmt.Println(n)
		} else {
			fmt.Println(result)
		}
	}
}