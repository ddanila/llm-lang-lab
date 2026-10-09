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
	line1, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields := strings.Fields(line1)
	if len(fields) < 2 {
		return
	}

	n, _ := strconv.Atoi(fields[0])
	q, _ := strconv.Atoi(fields[1])

	// Read N integers
	arr := make([]int64, n)
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		fields = strings.Fields(line)
		if len(fields) > 0 {
			val, _ := strconv.ParseInt(fields[0], 10, 64)
			arr[i] = val
		}
	}

	// Read Q queries
	queryLines := make([]string, q)
	for i := 0; i < q; i++ {
		line, _ := reader.ReadString('\n')
		fields = strings.Fields(line)
		if len(fields) > 0 {
			queryLines[i] = fields[0]
		}
	}

	// Process queries
	for _, qline := range queryLines {
		x, _ := strconv.ParseInt(qline, 10, 64)

		// Binary search for first element >= x
		left := 0
		right := n - 1
		result := n

		for left <= right {
			mid := left + (right-left)/2
			if arr[mid] >= x {
				result = mid
				right = mid - 1
			} else {
				left = mid + 1
			}
		}

		fmt.Println(result)
	}
}