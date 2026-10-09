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

	if q == 0 {
		return
	}

	// Read N integers (nondecreasing order)
	arr := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &arr[i])
	}

	// Process Q queries
	queries := make([]int64, q)
	for i := 0; i < q; i++ {
		fmt.Fscan(reader, &queries[i])
	}

	// For each query, find the first element >= x using binary search (or linear since N is small)
	// Since N <= 200, we can use a simple loop or bisect. Let's use a simple loop for clarity.
	for _, x := range queries {
		idx := -1
		for i, val := range arr {
			if val >= x {
				idx = i
				break
			}
		}
		fmt.Println(idx)
	}
}