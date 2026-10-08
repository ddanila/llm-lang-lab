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
	
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	
	if len(tokens) < 2 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	a := make([]int64, n)
	for i := 0; i < n && i < len(tokens)-2; i++ {
		val, _ := strconv.ParseInt(tokens[i+2], 10, 64)
		a[i] = val
	}
	
	if q == 0 {
		return
	}
	
	queryTokens := make([]string, 0, q)
	for _, token := range tokens[n+2:] {
		queryTokens = append(queryTokens, token)
	}
	
	if len(queryTokens) < q {
		line, _ := reader.ReadString('\n')
		tokens2 := strings.Fields(line)
		queryTokens = append(queryTokens, tokens2...)
	}
	
	for _, xStr := range queryTokens[:q] {
		x, _ := strconv.ParseInt(xStr, 10, 64)
		
		low, high := 0, n-1
		result := n
		
		for low <= high {
			mid := (low + high) / 2
			if a[mid] >= x {
				result = mid
				high = mid - 1
			} else {
				low = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}