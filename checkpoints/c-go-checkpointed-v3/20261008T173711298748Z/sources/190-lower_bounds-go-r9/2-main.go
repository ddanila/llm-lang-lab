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
	fmt.Fscan(reader, &n, &q)

	// Read N sorted integers
	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &a[i])
	}

	// Process Q queries
	if q > 0 {
		out := make([]string, q)
		for qi := 0; qi < q; qi++ {
			var x int
			fmt.Fscan(reader, &x)

			// Binary search for first element >= x
			idx := lowerBound(a, x)

			if idx == -1 {
				out[qi] = fmt.Sprintf("%d", n)
			} else {
				out[qi] = fmt.Sprintf("%d", idx)
			}
		}
		for _, s := range out {
			fmt.Println(s)
		}
	}
}

func lowerBound(arr []int, val int) int {
	left, right := 0, len(arr)
	for left < right {
		mid := left + (right-left)/2
		if arr[mid] >= val {
			right = mid
		} else {
			left = mid + 1
		}
	}
	return left
}