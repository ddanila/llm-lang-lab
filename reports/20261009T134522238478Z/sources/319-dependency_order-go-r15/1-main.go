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
	
	// Read all input into a single string and tokenize it
	input, err := reader.ReadString('\n')
	if err != nil && err != io.EOF {
		os.Exit(1)
	}
	
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("")
		return
	}
	
	N, err := strconv.Atoi(tokens[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	
	M, err := strconv.Atoi(tokens[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	
	// Build adjacency list and in-degree count
	adj := make([][]int, N)
	inDegree := make([]int, N)
	
	idx := 2
	for i := 0; i < M && idx < len(tokens); i++ {
		u, err := strconv.Atoi(tokens[idx])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(tokens[idx+1])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		
		// u must precede v, so edge is u -> v
		adj[u] = append(adj[u], v)
		inDegree[v]++
		idx += 2
	}
	
	// Kahn's algorithm with priority to smallest node
	// Use a min-heap approach: always pick smallest available node
	
	result := make([]int, 0, N)
	
	// Track which nodes have been processed
	processed := make([]bool, N)
	
	for len(result) < N {
		// Find all nodes with in-degree 0 that haven't been processed
		var candidates []int
		for i := 0; i < N; i++ {
			if !processed[i] && inDegree[i] == 0 {
				candidates = append(candidates, i)
			}
		}
		
		if len(candidates) == 0 {
			// No candidates but we haven't processed all nodes -> cycle
			fmt.Println("ERROR")
			return
		}
		
		// Pick the smallest candidate
		best := candidates[0]
		for _, c := range candidates {
			if c < best {
				best = c
			}
		}
		
		result = append(result, best)
		processed[best] = true
		
		// Decrease in-degree of neighbors
		for _, neighbor := range adj[best] {
			inDegree[neighbor]--
		}
	}
	
	// Output result
	fmt.Print(strings.Join(formatIntSlice(result), " "))
	fmt.Println()
}

func formatIntSlice(slice []int) []string {
	result := make([]string, len(slice))
	for i, v := range slice {
		result[i] = strconv.Itoa(v)
	}
	return result
}