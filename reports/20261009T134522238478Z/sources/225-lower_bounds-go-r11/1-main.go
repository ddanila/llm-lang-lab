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
	lineNum := 2
	
	for i := 0; i < N; i++ {
		if lineNum >= len(tokens) {
			line, _ := reader.ReadString('\n')
			tokens = strings.Fields(line)
		}
		arr[i], _ = strconv.Atoi(tokens[lineNum])
		lineNum++
		
		if lineNum >= len(tokens) {
			line, _ := reader.ReadString('\n')
			tokens = strings.Fields(line)
		}
		if i < N-1 {
			arr[i+1], _ = strconv.Atoi(tokens[lineNum])
			lineNum++
		}
	}
	
	// Read Q integers
	for qIdx := 0; qIdx < Q; qIdx++ {
		if lineNum >= len(tokens) {
			line, _ := reader.ReadString('\n')
			tokens = strings.Fields(line)
		}
		
		xStr := tokens[lineNum]
		lineNum++
		
		if lineNum >= len(tokens) {
			line, _ := reader.ReadString('\n')
			tokens = strings.Fields(line)
		}
		
		x, _ := strconv.Atoi(tokens[lineNum])
		
		// Binary search for first element >= x
		low, high := 0, N-1
		result := N
		
		for low <= high {
			mid := (low + high) / 2
			if arr[mid] >= int64(x) {
				result = mid
				high = mid - 1
			} else {
				low = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}