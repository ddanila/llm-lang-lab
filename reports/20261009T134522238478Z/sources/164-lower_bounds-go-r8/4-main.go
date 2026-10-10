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

	// Read array elements (nondecreasing order)
	a := make([]int, n)
	for i := 0; i < n; i++ {
		var val int
		fmt.Fscanf(reader, "%d", &val)
		a[i] = val
	}

	// Process Q queries
	for i := 0; i < q; i++ {
		var x int
		fmt.Fscanf(reader, "%d", &x)

		// Binary search for first element >= x
		idx := lowerBound(a, x)

		if idx == len(a) {
			fmt.Println(n)
		} else {
			fmt.Println(idx)
		}
	}
}

func lowerBound(arr []int, target int) int {
	left, right := 0, len(arr)
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