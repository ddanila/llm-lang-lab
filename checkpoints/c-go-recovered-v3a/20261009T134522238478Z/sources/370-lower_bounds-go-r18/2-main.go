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
	
	// Read all input from stdin until EOF
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	
	// If we haven't read anything yet, try reading more
	if len(tokens) == 0 {
		// Try to read more lines if available
		for {
			line, err := reader.ReadString('\n')
			if err != nil || line == "" {
				break
			}
			tokens = append(tokens, strings.Fields(line)...)
		}
	}
	
	if len(tokens) == 0 {
		return
	}
	
	n, err := strconv.Atoi(tokens[0])
	if err != nil || n < 0 || n > 200 {
		return
	}
	
	q, err := strconv.Atoi(tokens[1])
	if err != nil || q < 0 || q > 200 {
		return
	}
	
	// Read N integers for the array
	array := make([]int64, n)
	idx := 2
	
	for i := 0; i < n && idx < len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		array[i] = val
		idx++
	}
	
	// Read Q queries
	for j := 0; j < q && idx < len(tokens); j++ {
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