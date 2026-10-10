package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read N and Q
	var n, q int
	fmt.Fscanf(reader, "%d %d", &n, &q)
	
	// Read N sorted integers
	arr := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Fscanf(reader, "%d", &arr[i])
	}
	
	// Process Q queries
	if q > 0 {
		var x int64
		for i := 0; i < q; i++ {
			fmt.Fscanf(reader, "%d", &x)
			
			// Binary search for first element >= x
			idx := lowerBound(arr, x)
			
			if idx == n {
				fmt.Println(n)
			} else {
				fmt.Println(idx)
			}
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