package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	input := bufio.NewReader(os.Stdin)
	
	line1, err := input.ReadString('\n')
	if err != nil {
		return
	}
	tokens := split(line1)
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])

	arr := make([]int64, n)
	for i := 0; i < n; i++ {
		line, _ := input.ReadString('\n')
		tokens = split(line)
		arr[i] = int64(atoiSafe(tokens[0]))
	}

	for i := 0; i < q; i++ {
		line, _ := input.ReadString('\n')
		tokens = split(line)
		queryVal := int64(atoiSafe(tokens[0]))
		
		result := findLowerBound(arr, queryVal)
		fmt.Println(result)
	}
}

func split(s string) []string {
	var parts []string
	start := 0
	for i := 0; i < len(s); i++ {
		if s[i] == '\n' || s[i] == ' ' || s[i] == '\t' {
			parts = append(parts, s[start:i])
			i++
		}
	}
	if start <= len(s) {
		parts = append(parts, s[start:])
	}
	return parts
}

func atoiSafe(s string) int {
	val, _ := strconv.Atoi(s)
	return val
}

func findLowerBound(arr []int64, target int64) int {
	left := 0
	right := len(arr)

	for left < right {
		mid := left + (right-left)/2
		if arr[mid] >= target {
			right = mid
		} else {
			left = mid + 1
		}
	}

	return left
}