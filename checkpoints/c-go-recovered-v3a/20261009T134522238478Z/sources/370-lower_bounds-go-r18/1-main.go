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
	
	// Read N integers for the array
	array := make([]int64, n)
	idx := 2
	for i := 0; i < n; i++ {
		if idx < len(tokens) {
			val, _ := strconv.ParseInt(tokens[idx], 10, 64)
			array[i] = val
			idx++
		}
	}
	
	// Read Q queries
	for j := 0; j < q; j++ {
		if idx >= len(tokens) {
			break
		}
		
		queryVal, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		
		// Binary search for first element >= queryVal
		result := lowerBound(array, queryVal)
		fmt.Println(result)
	}
}

func lowerBound(arr []int64, val int64) int {
	l, r := 0, len(arr)
	
	for l < r {
		mid := l + (r-l)/2
		if arr[mid] >= val {
			r = mid
		} else {
			l = mid + 1
		}
	}
	
	return l
}