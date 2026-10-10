package main

import (
	"fmt"
	"sort"
)

func main() {
	var n, q int
	fmt.Fscan(&n, &q)

	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(&a[i])
	}

	// Input is already nondecreasing, but we'll sort to be safe.
	sort.Slice(a, func(i, j int) bool {
		return a[i] <= a[j]
	})

	for i := 0; i < q; i++ {
		var x int
		fmt.Fscan(&x)
		idx := sort.SearchInts(a, x)
		fmt.Println(idx)
	}
}