package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	if !scanner.Scan() {
		return
	}
	line := scanner.Text()
	var N, Q int
	fmt.Sscanf(line, "%d %d", &N, &Q)

	a := make([]int64, N)
	for i := 0; i < N; i++ {
		if !scanner.Scan() {
			break
		}
		valStr := scanner.Text()
		fmt.Sscanf(valStr, "%d", &a[i])
	}

	var buf []byte
	buf = append(buf, '\n')

	for q := 0; q < Q; q++ {
		if !scanner.Scan() {
			break
		}
		x, _ := strconv.ParseInt(scanner.Text(), 10, 64)

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