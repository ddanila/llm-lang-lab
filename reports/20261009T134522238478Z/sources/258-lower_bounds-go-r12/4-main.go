package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var n, q int
	fmt.Fscanf(reader, "%d %d", &n, &q)

	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscanf(reader, "%d", &a[i])
	}

	for i := 0; i < q; i++ {
		var x int
		fmt.Fscanf(reader, "%d", &x)
		
		idx := n
		for j := 0; j < n; j++ {
			if a[j] >= x {
				idx = j
				break
			}
		}
		fmt.Println(idx)
	}
}