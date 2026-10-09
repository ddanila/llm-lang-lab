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
	
	// Read all tokens from stdin
	input, err := reader.ReadString('\n')
	if err != nil && input == "" {
		return
	}
	tokens := strings.Fields(input)
	
	idx := 0
	var N, Q int
	
	if len(tokens) >= idx+2 {
		N, _ = strconv.Atoi(tokens[idx])
		Q, _ = strconv.Atoi(tokens[idx+1])
		idx += 2
		
		if N == 0 || Q == 0 {
			return
		}
		
		var arr [200]int
		for i := 0; i < N && idx < len(tokens); i++ {
			arr[i], _ = strconv.Atoi(tokens[idx])
			idx++
		}
		
		for i := 0; i < Q && idx < len(tokens); i++ {
			x, _ := strconv.Atoi(tokens[idx])
			idx++
			
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