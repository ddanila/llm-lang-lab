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
	
	// Read all input until EOF
	inputs := []string{}
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		inputs = append(inputs, line)
	}
	
	tokens := strings.Fields(strings.Join(inputs, ""))
	
	if len(tokens) == 0 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	var arr []int64
	idx := 2
	for i := 0; i < N; i++ {
		if idx >= len(tokens) {
			break
		}
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		arr = append(arr, val)
		idx++
	}
	
	var queries []int64
	for i := 0; i < Q; i++ {
		if idx >= len(tokens) {
			break
		}
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		queries = append(queries, val)
		idx++
	}
	
	for _, x := range queries {
		index := lowerBound(arr, x)
		fmt.Println(index)
	}
}

func lowerBound(arr []int64, x int64) int {
	l, r := 0, len(arr)
	for l < r {
		mid := l + (r-l)/2
		if arr[mid] >= x {
			r = mid
		} else {
			l = mid + 1
		}
	}
	return l
}