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

	// Read all remaining input as a single stream of tokens
	tokens := make([]string, 0)
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		fields := strings.Fields(line)
		tokens = append(tokens, fields...)
	}

	if len(tokens) < 2 {
		return
	}

	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])

	arr := make([]int64, n)
	for i := 0; i < n && i+1 <= len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[i+1], 10, 64)
		arr[i] = val
	}

	queryTokens := make([]string, 0)
	idx := 2 + n
	for idx < len(tokens) && len(queryTokens) < q {
		queryTokens = append(queryTokens, tokens[idx])
		idx++
	}

	// Process queries - use linear scan since array is sorted
	for _, qline := range queryTokens {
		x, _ := strconv.ParseInt(qline, 10, 64)

		// Linear search for first element >= x
		result := n
		for i := 0; i < n; i++ {
			if arr[i] >= x {
				result = i
				break
			}
		}

		fmt.Println(result)
	}
}