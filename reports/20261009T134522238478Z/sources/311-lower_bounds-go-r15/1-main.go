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
	
	// Read all input into a single string and tokenize
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	tokens := strings.Fields(input)
	
	if len(tokens) == 0 {
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
	
	// Read n integers for the array
	array := make([]int64, n)
	for i := 0; i < n; i++ {
		idx := 2 + i
		if idx >= len(tokens) {
			break
		}
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		array[i] = val
	}
	
	// Read q query integers
	queries := make([]int64, q)
	for i := 0; i < q; i++ {
		idx := 2 + n + i
		if idx >= len(tokens) {
			break
		}
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		queries[i] = val
	}
	
	// For each query, find the first element >= x using binary search (lower bound)
	for i := 0; i < q; i++ {
		x := queries[i]
		
		// Binary search for first element >= x
		left, right := 0, n-1
		result := n // Default if not found
		
		for left <= right {
			mid := left + (right-left)/2
			if array[mid] >= x {
				result = mid
				right = mid - 1
			} else {
				left = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}