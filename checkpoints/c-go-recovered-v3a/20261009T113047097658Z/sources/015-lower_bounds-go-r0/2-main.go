package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	tokens := []string{}
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		
		// Split line into tokens
		words := []string{}
		current := ""
		for _, c := range line {
			if c == ' ' || c == '\t' || c == '\r' || c == '\n' {
				if current != "" {
					words = append(words, current)
					current = ""
				}
			} else {
				current += string(c)
			}
		}
		if current != "" {
			words = append(words, current)
		}
		
		tokens = append(tokens, words...)
	}
	
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	arr := make([]int64, N)
	for i := 0; i < N; i++ {
		arr[i], _ = strconv.ParseInt(tokens[2+i], 10, 64)
	}
	
	// Process queries
	queryIdx := 2 + N
	for i := 0; i < Q; i++ {
		if queryIdx >= len(tokens) {
			break
		}
		x, _ := strconv.ParseInt(tokens[queryIdx], 10, 64)
		queryIdx++
		
		// Binary search for first element >= x
		l, r := 0, N-1
		idx := -1
		
		for l <= r {
			mid := (l + r) / 2
			if arr[mid] >= x {
				idx = mid
				r = mid - 1
			} else {
				l = mid + 1
			}
		}
		
		if idx == -1 {
			fmt.Println(N)
		} else {
			fmt.Println(idx)
		}
	}
}