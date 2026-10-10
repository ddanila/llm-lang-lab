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
	
	// Read all lines until EOF
	var input strings.Builder
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		input.WriteString(line)
	}
	
	tokens := strings.Fields(input.String())
	
	if len(tokens) == 0 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	array := make([]int64, n)
	for i := 0; i < n && 2+i < len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[2+i], 10, 64)
		array[i] = val
	}
	
	queries := make([]int64, q)
	for i := 0; i < q && 2+n+i < len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[2+n+i], 10, 64)
		queries[i] = val
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