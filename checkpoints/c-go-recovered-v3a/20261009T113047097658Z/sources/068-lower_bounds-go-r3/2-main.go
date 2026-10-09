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
	
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	tokens := strings.Fields(input)
	if len(tokens) < 2 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	a := make([]int64, n)
	idx := 0
	for i := 0; i < n && idx < len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		a[i] = val
		idx++
	}
	
	queries := make([]int64, q)
	if q > 0 {
		queryInput, _ := reader.ReadString('\n')
		tokens2 := strings.Fields(queryInput)
		for i := 0; i < q && i < len(tokens2); i++ {
			val, _ := strconv.ParseInt(tokens2[i], 10, 64)
			queries[i] = val
		}
	}
	
	for _, x := range queries {
		low, high := 0, n-1
		result := n // default to n if not found
		
		for low <= high {
			mid := (low + high) / 2
			if a[mid] >= x {
				result = mid
				high = mid - 1
			} else {
				low = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}