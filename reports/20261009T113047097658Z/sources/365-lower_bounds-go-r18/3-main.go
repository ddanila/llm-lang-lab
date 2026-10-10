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
	
	allInput, _ := reader.ReadString('\n')
	tokens := strings.Fields(allInput)
	
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	arr := make([]int64, N)
	idx := 2
	for i := 0; i < N && idx < len(tokens); i++ {
		val, _ := strconv.ParseInt(tokens[idx], 10, 64)
		arr[i] = val
		idx++
	}
	
	queryIdx := 0
	for i := 0; i < Q && queryIdx+idx < len(tokens); i++ {
		query, _ := strconv.ParseInt(tokens[queryIdx], 10, 64)
		queryIdx++
		
		resultIdx := -1
		for j := 0; j < N; j++ {
			if arr[j] >= query {
				resultIdx = j
				break
			}
		}
		
		if resultIdx == -1 {
			fmt.Printf("%d\n", N)
		} else {
			fmt.Printf("%d\n", resultIdx)
		}
	}
}