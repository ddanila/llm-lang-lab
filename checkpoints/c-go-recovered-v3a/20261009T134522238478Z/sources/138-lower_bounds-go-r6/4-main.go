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
	
	if len(tokens) < 2 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	// Read N sorted integers
	arr := make([]int64, n)
	for i := 0; i < n && len(tokens) > 2+i; i++ {
		arr[i], _ = strconv.ParseInt(tokens[2+i], 10, 64)
	}
	
	// Process Q queries
	queryIdx := 2 + n
	for i := 0; i < q && queryIdx+1 < len(tokens); i++ {
		x, _ := strconv.ParseInt(tokens[queryIdx], 10, 64)
		queryIdx++
		
		// Binary search for first element >= x
		idx := lowerBound(arr, x)
		
		if idx == n {
			fmt.Println(n)
		} else {
			fmt.Println(idx)
		}
	}
}

func lowerBound(arr []int64, target int64) int {
	left := 0
	right := len(arr)
	
	for left < right {
		mid := left + (right-left)/2
		if arr[mid] >= target {
			right = mid
		} else {
			left = mid + 1
		}
	}
	
	return left
}