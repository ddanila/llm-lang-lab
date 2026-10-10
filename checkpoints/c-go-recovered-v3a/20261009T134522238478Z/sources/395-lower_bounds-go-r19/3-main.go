package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	
	if !scanner.Scan() {
		return
	}
	tokens := scanner.Bytes()
	tokenIdx := 0
	
	if tokenIdx >= len(tokens) {
		return
	}
	N, _ := strconv.Atoi(string(tokens[tokenIdx]))
	tokenIdx++
	
	if tokenIdx >= len(tokens) {
		return
	}
	Q, _ := strconv.Atoi(string(tokens[tokenIdx]))
	tokenIdx++
	
	var A []int
	for i := 0; i < N; i++ {
		if tokenIdx >= len(tokens) {
			break
		}
		val, _ := strconv.Atoi(string(tokens[tokenIdx]))
		A = append(A, val)
		tokenIdx++
	}
	
	var queries []int
	for i := 0; i < Q; i++ {
		if tokenIdx >= len(tokens) {
			break
		}
		val, _ := strconv.Atoi(string(tokens[tokenIdx]))
		queries = append(queries, val)
		tokenIdx++
	}
	
	if Q == 0 {
		return
	}
	
	for _, x := range queries {
		idx := lowerBound(A, x)
		fmt.Println(idx)
	}
}

func lowerBound(arr []int, target int) int {
	l, r := 0, len(arr)
	for l < r {
		mid := l + (r-l)/2
		if arr[mid] >= target {
			r = mid
		} else {
			l = mid + 1
		}
	}
	return l
}