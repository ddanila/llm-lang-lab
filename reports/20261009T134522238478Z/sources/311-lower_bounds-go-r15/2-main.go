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
	
	// Read all input
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	
	if len(tokens) == 0 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	array := make([]int64, n)
	for i := 0; i < n && 2+i < len(tokens); i++ {
		array[i], _ = strconv.ParseInt(tokens[2+i], 10, 64)
	}
	
	queries := make([]int64, q)
	for i := 0; i < q && 2+n+i < len(tokens); i++ {
		queries[i], _ = strconv.ParseInt(tokens[2+n+i], 10, 64)
	}
	
	// Process each query with binary search (lower bound)
	for _, x := range queries {
		left, right := 0, n-1
		result := n
		
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