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
	
	// Read N and Q
	if !scanner.Scan() {
		return
	}
	input := strings.TrimSpace(scanner.Text())
	parts := strings.Fields(input)
	
	if len(parts) < 2 {
		return
	}
	
	N, err1 := strconv.Atoi(parts[0])
	Q, err2 := strconv.Atoi(parts[1])
	
	if err1 != nil || err2 != nil {
		return
	}
	
	// Read N integers
	arr := make([]int64, 0, N)
	for i := 0; i < N; i++ {
		if !scanner.Scan() {
			break
		}
		val := strings.Fields(scanner.Text())
		if len(val) > 0 {
			arr = append(arr, val[0])
		}
	}
	
	// Read Q queries
	for i := 0; i < Q; i++ {
		if !scanner.Scan() {
			break
		}
		vals := strings.Fields(scanner.Text())
		if len(vals) == 0 {
			continue
		}
		
		x, err := strconv.ParseInt(vals[0], 10, 64)
		if err != nil {
			continue
		}
		
		// Find first index where arr[i] >= x using binary search
		idx := lowerBound(arr, x)
		fmt.Println(idx)
	}
}

func lowerBound(arr []int64, target int64) int {
	left, right := 0, len(arr)
	
	for left < right {
		mid := left + (right-left)/2
		if arr[mid] >= target {
			right = mid
		} else {
			left = mid + 1
		}
	}
	
	return left
}