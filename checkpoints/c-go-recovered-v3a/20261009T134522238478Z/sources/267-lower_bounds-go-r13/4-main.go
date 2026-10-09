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
	
	var tokens []string
	buf := make([]byte, 1024)
	
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			tokens = append(tokens, string(buf[:n]))
		}
		if err != nil {
			break
		}
	}
	
	allTokens := strings.Fields(strings.Join(tokens, ""))
	idx := 0
	
	if idx+1 >= len(allTokens) {
		return
	}
	var N int
	N, _ = strconv.Atoi(allTokens[idx])
	idx++
	var Q int
	Q, _ = strconv.Atoi(allTokens[idx])
	idx++
	
	if N == 0 || Q == 0 {
		return
	}
	
	var arr [200]int
	for i := 0; i < N && idx < len(allTokens); i++ {
		arr[i], _ = strconv.Atoi(allTokens[idx])
		idx++
	}
	
	for i := 0; i < Q && idx < len(allTokens); i++ {
		x, _ := strconv.Atoi(allTokens[idx])
		idx++
		
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