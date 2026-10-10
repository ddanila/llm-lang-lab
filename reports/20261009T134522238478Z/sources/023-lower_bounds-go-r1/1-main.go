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

	// Read all input into a single string
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		return
	}

	idx := 0
	N, _ := strconv.Atoi(tokens[idx])
	idx++
	Q, _ := strconv.Atoi(tokens[idx])
	idx++

	if N > 0 {
		arr := make([]int64, N)
		for i := 0; i < N; i++ {
			arr[i], _ = strconv.ParseInt(tokens[idx], 10, 64)
			idx++
		}
		// Queries follow
		if Q > 0 {
			for q := 0; q < Q; q++ {
				x, _ := strconv.ParseInt(tokens[idx], 10, 64)
				idx++

				// Binary search for first element >= x
				l, r := 0, N-1
				result := N
				for l <= r {
					m := l + (r-l)/2
					if arr[m] >= x {
						result = m
						r = m - 1
					} else {
						l = m + 1
					}
				}
				fmt.Println(result)
			}
		}
	}
}