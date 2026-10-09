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
	
	if q <= 0 {
		return
	}
	
	idx := 2
	arr := make([]int64, n)
	for i := 0; i < n; i++ {
		arr[i], _ = strconv.Atoi(tokens[idx])
		idx++
	}
	
	queryIdx := idx
	queries := make([]int64, q)
	for i := 0; i < q; i++ {
		if queryIdx >= len(tokens) {
			break
		}
		val, _ := strconv.Atoi(tokens[queryIdx])
		queries[i] = int64(val)
		queryIdx++
	}
	
	for _, x := range queries {
		low, high := 0, n-1
		result := n
		for low <= high {
			mid := low + (high-low)/2
			if arr[mid] >= x {
				result = mid
				high = mid - 1
			} else {
				low = mid + 1
			}
		}
		fmt.Println(result)
	}
}