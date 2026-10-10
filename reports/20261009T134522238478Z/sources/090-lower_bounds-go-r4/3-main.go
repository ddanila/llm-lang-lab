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

	var a []int64
	if n > 0 && len(tokens) >= 2+n {
		a = make([]int64, n)
		for i := 0; i < n; i++ {
			val, _ := strconv.ParseInt(tokens[2+i], 10, 64)
			a[i] = val
		}
	}

	if q > 0 && len(tokens) >= 2+n+q {
		for i := 0; i < q; i++ {
			x, _ := strconv.ParseInt(tokens[2+n+i], 10, 64)
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