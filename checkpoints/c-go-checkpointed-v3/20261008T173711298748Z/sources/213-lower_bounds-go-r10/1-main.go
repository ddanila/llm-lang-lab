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
	
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	tokens := strings.Fields(input)
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	if N == 0 && Q == 0 {
		return
	}
	
	var arr []int64
	for i := 0; i < N; i++ {
		arr = append(arr, parseInt(tokens[i+2]))
	}
	
	var queries []int64
	idx := 2 + N
	for i := 0; i < Q; i++ {
		if idx >= len(tokens) {
			break
		}
		queries = append(queries, parseInt(tokens[idx+i]))
	}
	
	if Q == 0 {
		return
	}
	
	output := make([]string, Q)
	for i, x := range queries {
		idx := lowerBound(arr, x)
		output[i] = strconv.Itoa(idx)
	}
	
	fmt.Fprintln(os.Stdout, strings.Join(output, "\n"))
}

func parseInt(s string) int64 {
	val, _ := strconv.ParseInt(s, 10, 64)
	return val
}

func lowerBound(arr []int64, x int64) int {
	l, r := 0, len(arr)
	for l < r {
		m := (l + r) / 2
		if arr[m] >= x {
			r = m
		} else {
			l = m + 1
		}
	}
	return l
}