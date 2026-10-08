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
	
	// Read all input into a single string
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	if len(input) == 0 {
		return
	}
	
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
	
	// Read array elements (n integers)
	arr := make([]int64, n)
	idx := 2
	for i := 0; i < n; i++ {
		if idx >= len(tokens) {
			break
		}
		arr[i], _ = strconv.ParseInt(tokens[idx], 10, 64)
		idx++
	}
	
	// Read queries (q integers)
	for i := 0; i < q; i++ {
		if idx >= len(tokens) {
			break
		}
		queryVal, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		
		// Binary search for first element >= queryVal
		// Since array is nondecreasing, we can use binary search
		left, right := 0, n-1
		result := n // default if not found
		
		for left <= right {
			mid := left + (right-left)/2
			if arr[mid] >= queryVal {
				result = mid
				right = mid - 1
			} else {
				left = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}