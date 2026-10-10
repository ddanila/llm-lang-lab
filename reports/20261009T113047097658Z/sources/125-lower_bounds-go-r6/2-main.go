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
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	tokens := strings.Fields(line)
	if len(tokens) < 2 {
		return
	}

	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])

	// Read N integers (nondecreasing order)
	arr := make([]int64, N)
	for i := 0; i < N; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && line == "" {
			break
		}
		tokens := strings.Fields(line)
		for j := range tokens {
			arr[i], _ = strconv.ParseInt(tokens[j], 10, 64)
			i++
			if i >= N {
				break
			}
		}
	}

	// Read Q query integers (may span multiple lines)
	queryTokens := []string{}
	for len(queryTokens) < Q {
		line, err := reader.ReadString('\n')
		if err != nil && line == "" {
			break
		}
		tokens := strings.Fields(line)
		queryTokens = append(queryTokens, tokens...)
	}

	// Process queries
	for _, qStr := range queryTokens[:Q] {
		x, _ := strconv.ParseInt(qStr, 10, 64)

		// Binary search for first element >= x
		l, r := 0, N-1
		result := N // default if not found
		for l <= r {
			mid := l + (r-l)/2
			if arr[mid] >= x {
				result = mid
				r = mid - 1
			} else {
				l = mid + 1
			}
		}

		fmt.Println(result)
	}
}