package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		return
	}

	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])

	if n > 0 {
		a := make([]int64, n)
		idx := 2
		for i := 0; i < n; i++ {
			val, _ := strconv.ParseInt(tokens[idx], 10, 64)
			a[i] = val
			idx++
		}

		if q > 0 && len(tokens) >= idx+q {
			for i := 0; i < q; i++ {
				x, _ := strconv.ParseInt(tokens[idx+i], 10, 64)
				l, r := 0, n-1
				ans := -1
				for l <= r {
					mid := (l + r) / 2
					if a[mid] >= x {
						ans = mid
						r = mid - 1
					} else {
						l = mid + 1
					}
				}
				if ans == -1 {
					fmt.Println(n)
				} else {
					fmt.Println(ans)
				}
			}
		}
	}
}