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
	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &a[i])
	}

	// Process Q queries
	for i := 0; i < q; i++ {
		var x int
		fmt.Fscan(reader, &x)

		// Binary search for first element >= x
		l, r := 0, n-1
		idx := n // default if not found

		for l <= r {
			mid := l + (r-l)/2
			if a[mid] >= x {
				idx = mid
				r = mid - 1
			} else {
				l = mid + 1
			}
		}

		fmt.Println(idx)
	}
}