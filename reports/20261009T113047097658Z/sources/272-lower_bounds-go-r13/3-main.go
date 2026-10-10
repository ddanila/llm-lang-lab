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
	
	// Read N and Q from first line
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	tokens := strings.Fields(line)
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	_ = Q
	
	// Read all remaining lines for array and queries
	var arr []int64
	var queryStrs []string
	
	for {
		line, err := reader.ReadString('\n')
		if err != nil && line == "" {
			break
		}
		
		tokens = strings.Fields(line)
		if len(tokens) == 0 {
			continue
		}
		
		// Check if this is array data (first N integers) or queries
		totalRead := len(arr) + len(queryStrs)
		
		for _, tok := range tokens {
			val, _ := strconv.ParseInt(tok, 10, 64)
			if totalRead < N {
				arr = append(arr, val)
			} else {
				queryStrs = append(queryStrs, tok)
			}
			totalRead++
		}
	}
	
	// Process queries
	for _, qstr := range queryStrs {
		x, _ := strconv.ParseInt(qstr, 10, 64)
		
		// Binary search for first element >= x
		left, right := 0, N-1
		result := N
		
		for left <= right {
			mid := left + (right-left)/2
			if arr[mid] >= x {
				result = mid
				right = mid - 1
			} else {
				left = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}