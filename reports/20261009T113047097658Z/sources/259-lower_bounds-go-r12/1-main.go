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

	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		return
	}

	q, err := strconv.Atoi(tokens[1])
	if err != nil {
		return
	}

	idx := 2
	a := make([]int64, n)
	for i := 0; i < n; i++ {
		a[i], _ = strconv.ParseInt(tokens[idx+i], 10, 64)
	}

	if q == 0 {
		return
	}

	queryStart := idx + n
	queryTokens := tokens[queryStart:]

	for _, qStr := range queryTokens {
		x, _ := strconv.ParseInt(qStr, 10, 64)
		
		// Binary search for first element >= x
		left, right := 0, n-1
		result := n
		
		for left <= right {
			mid := left + (right-left)/2
			if a[mid] >= x {
				result = mid
				right = mid - 1
			} else {
				left = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}