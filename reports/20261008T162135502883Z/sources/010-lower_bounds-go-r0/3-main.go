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
	
	// Read all input from stdin line by line
	var input strings.Builder
	for {
		line, err := reader.ReadString('\n')
		if err != nil || len(line) == 0 {
			break
		}
		input.WriteString(line)
	}
	
	tokens := strings.Fields(input.String())
	if len(tokens) < 2 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	// Read array elements (n integers)
	arr := make([]int64, n)
	idx := 2
	for i := 0; i < n && idx < len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		arr[i] = val
		idx++
	}
	
	// Read queries (q integers) and process them
	for i := 0; i < q && idx < len(tokens); i++ {
		queryVal, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		
		// Binary search for first element >= queryVal
		left, right := 0, n-1
		result := n
		
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