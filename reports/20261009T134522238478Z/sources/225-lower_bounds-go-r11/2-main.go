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
	
	tokens := strings.Fields(line1)
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	// Read N integers
	arr := make([]int64, N)
	idx := 0
	
	for i := 0; i < N; i++ {
		if idx >= len(tokens) {
			line, _ := reader.ReadString('\n')
			tokens = strings.Fields(line)
		}
		arr[i], _ = strconv.ParseInt(tokens[idx], 10, 64)
		idx++
	}
	
	// Read Q integers
	for qIdx := 0; qIdx < Q; qIdx++ {
		if idx >= len(tokens) {
			line, _ := reader.ReadString('\n')
			tokens = strings.Fields(line)
		}
		
		x, _ := strconv.ParseInt(tokens[idx], 10, 64)
		
		// Binary search for first element >= x
		low, high := 0, N-1
		result := N
		
		for low <= high {
			mid := (low + high) / 2
			if arr[mid] >= x {
				result = mid
				high = mid - 1
			} else {
				low = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}