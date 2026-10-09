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

	// Read N and Q
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	if len(tokens) < 2 {
		return
	}

	N, err := strconv.Atoi(tokens[0])
	if err != nil {
		return
	}
	Q, err := strconv.Atoi(tokens[1])
	if err != nil {
		return
	}

	if Q == 0 {
		return
	}

	// Read array elements
	a := make([]int64, N)
	for i := 0; i < N; i++ {
		token := readToken(reader)
		a[i], _ = strconv.ParseInt(token, 10, 64)
	}

	// Read queries and process each
	for q := 0; q < Q; q++ {
		token := readToken(reader)
		x, _ := strconv.ParseInt(token, 10, 64)

		// Binary search for first element >= x
		idx := lowerBound(a, x)
		fmt.Println(idx)
	}
}

func readToken(r *bufio.Reader) string {
	for {
		line, err := r.ReadString('\n')
		if err == nil {
			tokens := strings.Fields(line)
			for _, tok := range tokens {
				if tok != "" {
					return tok
				}
			}
		}
	}
}

func lowerBound(a []int64, x int64) int {
	l, r := 0, len(a)
	for l < r {
		m := (l + r) / 2
		if a[m] >= x {
			r = m
		} else {
			l = m + 1
		}
	}
	return l
}