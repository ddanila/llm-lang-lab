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
	
	arr := make([]int64, N)
	for i := 0; i < N; i++ {
		if len(tokens) <= i+2 {
			break
		}
		val, _ := strconv.ParseInt(tokens[i+2], 10, 64)
		arr[i] = val
	}
	
	for i := 0; i < Q; i++ {
		if len(tokens) <= i+N+2 {
			break
		}
		query, _ := strconv.ParseInt(tokens[i+N+2], 10, 64)
		
		idx := -1
		for j := 0; j < N; j++ {
			if arr[j] >= query {
				idx = j
				break
			}
		}
		
		if idx == -1 {
			fmt.Printf("%d\n", N)
		} else {
			fmt.Printf("%d\n", idx)
		}
	}
}