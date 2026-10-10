package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	var n, q int
	if !scanner.Scan() {
		return
	}
	fmt.Sscanf(scanner.Text(), "%d %d", &n, &q)

	a := make([]int64, n)
	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		fmt.Fscanf(os.Stdin, "%d", &a[i])
	}

	for i := 0; i < q; i++ {
		var x int64
		if !scanner.Scan() {
			break
		}
		fmt.Fscanf(os.Stdin, "%d", &x)

		low, high := 0, n-1
		idx := -1
		for low <= high {
			mid := low + (high-low)/2
			if a[mid] >= x {
				idx = mid
				high = mid - 1
			} else {
				low = mid + 1
			}
		}

		if idx == -1 {
			fmt.Println(n)
		} else {
			fmt.Println(idx)
		}
	}
}