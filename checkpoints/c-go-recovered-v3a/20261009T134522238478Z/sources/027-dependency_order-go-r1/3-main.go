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
	
	// Read all input as a single string and tokenize it
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	N, err := strconv.Atoi(tokens[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	
	M, _ := strconv.Atoi(tokens[1])
	
	// Handle N=0 case
	if N == 0 {
		fmt.Println("")
		return
	}
	
	// Build adjacency list and in-degree array
	adj := make([][]int, N)
	inDegree := make([]int, N)
	
	for i := 2; i < len(tokens); i += 2 {
		if i+1 >= len(tokens) {
			break
		}
		u, err := strconv.Atoi(tokens[i])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(tokens[i+1])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		
		// Self-edges are allowed but don't affect topological order (can be ignored for ordering)
		if u == v {
			continue
		}
		
		adj[u] = append(adj[u], v)
		inDegree[v]++
	}
	
	// Kahn's algorithm with priority to lexicographically smallest node
	result := make([]int, 0, N)
	
	for i := 0; i < N; i++ {
		// Find the smallest index with inDegree 0 and not yet processed
		minIdx := -1
		for j := 0; j < N; j++ {
			if inDegree[j] == 0 && !visited(j, result) {
				minIdx = j
				break
			}
		}
		
		if minIdx == -1 {
			// No node with inDegree 0 available - cycle detected
			fmt.Println("ERROR")
			return
		}
		
		result = append(result, minIdx)
		
		// Decrease in-degree of neighbors
		for _, neighbor := range adj[minIdx] {
			inDegree[neighbor]--
		}
	}
	
	// Check if we processed all nodes
	if len(result) != N {
		fmt.Println("ERROR")
		return
	}
	
	// Output result
	for i, node := range result {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(node)
	}
	fmt.Println()
}

func visited(result []int, n int) bool {
	for _, r := range result {
		if r == n {
			return true
		}
	}
	return false
}