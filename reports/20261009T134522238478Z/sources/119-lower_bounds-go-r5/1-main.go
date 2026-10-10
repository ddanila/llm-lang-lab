package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	var n, q int
	fmt.Fscan(reader, &n, &q)

	if n == 0 && q == 0 {
		return
	}

	arr := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &arr[i])
	}

	for j := 0; j < q; j++ {
		var x int64
		fmt.Fscan(reader, &x)

		low := 0
		high := n - 1
		idx := n

		for low <= high {
			mid := (low + high) / 2
			if arr[mid] >= x {
				idx = mid
				high = mid - 1
			} else {
				low = mid + 1
			}
		}

		fmt.Fprintln(os.Stdout, idx)
	}
}