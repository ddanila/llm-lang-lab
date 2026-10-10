package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	var N, Q int
	if !scanner.Scan() {
		return
	}
	fmt.Sscanf(scanner.Text(), "%d %d", &N, &Q)

	a := make([]int64, N)
	for i := 0; i < N; i++ {
		if !scanner.Scan() {
			break
		}
		fmt.Sscanf(scanner.Text(), "%d", &a[i])
	}

	var buf []byte
	buf = append(buf, '\n')

	for q := 0; q < Q; q++ {
		if !scanner.Scan() {
			break
		}
		xStr := scanner.Text()
		x, _ := strconv.ParseInt(xStr, 10, 64)

		idx := N
		l, r := 0, N-1
		for l <= r {
			mid := l + (r-l)/2
			if a[mid] >= x {
				idx = mid
				r = mid - 1
			} else {
				l = mid + 1
			}
		}

		buf = append(buf, fmt.Sprintf("%d\n", idx)...)
	}

	os.Stdout.Write(buf)
}