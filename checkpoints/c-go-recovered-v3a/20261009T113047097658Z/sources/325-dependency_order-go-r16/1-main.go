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

	incoming := make([]int, n)
	for i := range incoming {
		incoming[i] = 0
	}

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

		incoming[v]++
	}

	// Kahn's algorithm with min-heap simulation using sorted selection
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

		// Find minimum node in available (simple linear scan since n <= 20)
		minNode := available[0]
		for i := 1; i < count; i++ {
			if available[i] < minNode {
				minNode = available[i]
			}
		}

		result[step] = minNode
		step++

		// Remove minNode from available and update incoming counts
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

		// Update incoming counts for neighbors
		// We need to find edges from minNode to other nodes
		// Since we didn't store the graph, we need to recompute or store it
		// Let's rebuild the approach with adjacency list
	}

	// Actually, let's redo this properly with adjacency list
}