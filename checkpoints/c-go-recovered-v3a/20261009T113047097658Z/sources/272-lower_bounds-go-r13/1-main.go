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
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	tokens := strings.Fields(line)
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	// Read array elements
	var arr []int64
	for i := 0; i < N; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && line == "" {
			break
		}
		
		tokens = strings.Fields(line)
		for _, tok := range tokens {
			val, _ := strconv.ParseInt(tok, 10, 64)
			arr = append(arr, val)
		}
	}
	
	// Read queries and process
	if Q > 0 {
		for qIdx := 0; qIdx < Q; qIdx++ {
			line, err := reader.ReadString('\n')
			if err != nil && line == "" {
				break
			}
			
			tokens = strings.Fields(line)
			for _, tok := range tokens {
				x, _ := strconv.ParseInt(tok, 10, 64)
				
				// Binary search for first element >= x
				left, right := 0, N-1
				result := N
				
				for left <= right {
					mid := left + (right-left)/2
					if arr[mid] >= x {
						result = mid
						right = mid - 1
					} else {
						left = mid + 1
					}
				}
				
				fmt.Println(result)
			}
		}
	}
}