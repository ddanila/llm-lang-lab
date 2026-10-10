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

	// For each query, find the first element >= x
	for _, x := range queries {
		idx := n // default to N if no element >= x exists
		for i, val := range arr {
			if val >= x {
				idx = i
				break
			}
		}
		fmt.Println(idx)
	}
}