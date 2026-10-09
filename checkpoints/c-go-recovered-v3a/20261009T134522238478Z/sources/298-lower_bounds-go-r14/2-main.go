package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	
	// Read all input at once for efficiency
	var input strings.Builder
	for scanner.Scan() {
		input.WriteString(scanner.Text())
		input.WriteByte('\n')
	}
	
	tokens := strings.Fields(input.String())
	if len(tokens) == 0 {
		return
	}

	idx := 0
	
	// Read N and Q
	N, _ := strconv.Atoi(tokens[idx])
	idx++
	Q, _ := strconv.Atoi(tokens[idx])
	idx++

	if Q == 0 {
		return
	}

	// Read array elements
	a := make([]int64, N)
	for i := 0; i < N; i++ {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		a[i] = val
		idx++
	}

	// Read queries and process each
	for q := 0; q < Q; q++ {
		x, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++

		// Binary search for first element >= x
		l, r := 0, len(a)
		for l < r {
			m := (l + r) / 2
			if a[m] >= x {
				r = m
			} else {
				l = m + 1
			}
		}
		fmt.Println(l)
	}
}