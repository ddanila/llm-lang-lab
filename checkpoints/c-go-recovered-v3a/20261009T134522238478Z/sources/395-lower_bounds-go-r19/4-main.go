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
	
	tokens := []string{}
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		for _, token := range strings.Fields(line) {
			tokens = append(tokens, token)
		}
	}
	
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	tokenIdx := 1
	
	if N > 0 && tokenIdx >= len(tokens) {
		return
	}
	for i := 0; i < N; i++ {
		if tokenIdx >= len(tokens) {
			break
		}
		A = append(A, _int(tokens[tokenIdx]))
		tokenIdx++
	}
	
	if tokenIdx >= len(tokens) {
		return
	}
	Q, _ := strconv.Atoi(tokens[tokenIdx])
	tokenIdx++
	
	for i := 0; i < Q; i++ {
		if tokenIdx >= len(tokens) {
			break
		}
		queries = append(queries, _int(tokens[tokenIdx]))
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

var A []int
var queries []int

func _int(s string) int {
	i, _ := strconv.Atoi(s)
	return i
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