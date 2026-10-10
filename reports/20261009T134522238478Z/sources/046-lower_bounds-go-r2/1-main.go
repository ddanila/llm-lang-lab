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
	if len(tokens) == 0 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	var arr []int64
	for i := 0; i < n; i++ {
		arr = append(arr, mustParseInt64(tokens[i+2]))
	}
	
	idx := 2 + n
	
	queryTokens := make([]string, q)
	for i := 0; i < q; i++ {
		if idx >= len(tokens) {
			break
		}
		queryTokens[i] = tokens[idx]
		idx++
	}
	
	var result []string
	for _, s := range queryTokens {
		if s == "" {
			continue
		}
		val, _ := strconv.ParseInt(s, 10, 64)
		
		bounds := findBounds(arr, val)
		if bounds.first >= n {
			result = append(result, "N") // Wait, should be N for none exists
			continue
		}
		result = append(result, fmt.Sprintf("%d", bounds.first))
	}
	
	for _, r := range result {
		fmt.Println(r)
	}
}

func mustParseInt64(s string) int64 {
	val, _ := strconv.ParseInt(s, 10, 64)
	return val
}

type Bounds struct {
	first int
	last  int
}

func findBounds(arr []int64, target int64) Bounds {
	left := 0
	right := len(arr) - 1
	
	for left <= right {
		mid := left + (right-left)/2
		if arr[mid] >= target {
			first = mid
			right = mid - 1
		} else {
			left = mid + 1
		}
	}
	
	return Bounds{first: left, last: len(arr)}
}

var first int

func (b *Bounds) SetFirst(v int) { b.first = v }