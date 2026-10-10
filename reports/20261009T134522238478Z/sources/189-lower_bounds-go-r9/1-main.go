package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Read N and Q
	var n, q int
	fmt.Fscan(reader, &n, &q)

	// Read N integers (sorted nondecreasingly)
	arr := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &arr[i])
	}

	// Process Q queries
	for j := 0; j < q; j++ {
		var x int
		fmt.Fscan(reader, &x)

		// Binary search for the first element >= x
		idx := lowerBound(arr, x)

		fmt.Println(idx)
	}
}

func lowerBound(arr []int, target int) int {
	left := 0
	right := len(arr) // exclusive upper bound

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