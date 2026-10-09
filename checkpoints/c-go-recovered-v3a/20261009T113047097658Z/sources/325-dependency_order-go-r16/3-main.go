package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var tokens []string
	for scanner.Scan() {
		tokens = append(tokens, strings.Fields(scanner.Text())...)
	}
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}

	n, err := strconv.Atoi(tokens[0])
	if err != nil || n < 0 || n > 20 {
		fmt.Println("ERROR")
		return
	}

	m, err := strconv.Atoi(tokens[1])
	if err != nil || m < 0 || m > 100 {
		fmt.Println("ERROR")
		return
	}

	// Handle N=0 case
	if n == 0 {
		fmt.Println()
		return
	}

	// Adjacency list for graph
	graph := make([][]int, n)
	incoming := make([]int, n)

	idx := 2
	for i := 0; i < m; i++ {
		if idx >= len(tokens) {
			fmt.Println("ERROR")
			return
		}
		u, err := strconv.Atoi(tokens[idx])
		if err != nil || u < 0 || u >= n {
			fmt.Println("ERROR")
			return
		}
		idx++

		if idx >= len(tokens) {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(tokens[idx])
		if err != nil || v < 0 || v >= n {
			fmt.Println("ERROR")
			return
		}
		idx++

		graph[u] = append(graph[u], v)
		incoming[v]++
	}

	// Kahn's algorithm with min-heap (using sorted selection since n is small)
	available := make([]int, n)
	count := 0
	for i := range incoming {
		if incoming[i] == 0 {
			available[count] = i
			count++
		}
	}

	result := make([]int, n)
	step := 0

	for step < n {
		if count == 0 {
			fmt.Println("ERROR")
			return
		}

		// Find minimum node in available
		minNode := available[0]
		for i := 1; i < count; i++ {
			if available[i] < minNode {
				minNode = available[i]
			}
		}

		result[step] = minNode
		step++

		// Remove minNode from available
		for i := 0; i < count; i++ {
			if available[i] == minNode {
				// Shift remaining elements left
				for j := i; j < count-1; j++ {
					available[j] = available[j+1]
				}
				count--
				break
			}
		}

		// Update incoming counts for neighbors of minNode
		for _, v := range graph[minNode] {
			incoming[v]--
			if incoming[v] == 0 {
				available[count] = v
				count++
			}
		}
	}

	// Output result
	fmt.Print(result[0])
	for i := 1; i < n; i++ {
		fmt.Printf(" %d", result[i])
	}
	fmt.Println()
}