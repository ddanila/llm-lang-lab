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
	
	tokens := make([]string, 0, 1000)
	line, err := reader.ReadString('\n')
	if err == nil && line != "" {
		tokens = append(tokens, strings.Fields(line)...)
	}
	
	// Read remaining lines if any
	for {
		line, err := reader.ReadString('\n')
		if err != nil || line == "" {
			break
		}
		tokens = append(tokens, strings.Fields(line)...)
	}
	
	if len(tokens) == 0 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	array := make([]int64, n)
	idx := 2
	
	for i := 0; i < n && idx < len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		array[i] = val
		idx++
	}
	
	for j := 0; j < q && idx < len(tokens); j++ {
		queryVal, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		
		result := lowerBound(array, queryVal)
		fmt.Println(result)
	}
}

func lowerBound(arr []int64, val int64) int {
	l, r := 0, len(arr)
	
	for l < r {
		mid := l + (r-l)/2
		if arr[mid] >= val {
			r = mid
		} else {
			l = mid + 1
		}
	}
	
	return l
}