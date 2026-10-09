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
	
	// Read all input as whitespace-separated tokens
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
	
	for i := 2; i < len(tokens); i++ {
		uStr := tokens[i]
		vStr := tokens[i+1]
		
		if i+1 >= len(tokens) {
			break
		}
		
		u, err := strconv.Atoi(uStr)
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		
		v, err := strconv.Atoi(vStr)
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		
		// Validate u and v are within range
		if u < 0 || u >= N || v < 0 || v >= N {
			fmt.Println("ERROR")
			return
		}
		
		adj[u] = append(adj[u], v)
		inDegree[v]++
		i += 1 // Skip the next token (v)
	}
	
	// Kahn's algorithm with lexicographically smallest selection
	result := make([]int, 0, N)
	visited := make([]bool, N)
	
	for len(result) < N {
		// Find all nodes with in-degree 0 and not yet visited
		candidates := []int{}
		for i := 0; i < N; i++ {
			if !visited[i] && inDegree[i] == 0 {
				candidates = append(candidates, i)
			}
		}
		
		if len(candidates) == 0 {
			// Cycle detected
			fmt.Println("ERROR")
			return
		}
		
		// Pick the smallest candidate (lexicographically first)
		minNode := candidates[0]
		for _, c := range candidates {
			if c < minNode {
				minNode = c
			}
		}
		
		result = append(result, minNode)
		visited[minNode] = true
		
		// Decrease in-degree of neighbors
		for _, neighbor := range adj[minNode] {
			inDegree[neighbor]--
		}
	}
	
	// Output result
	fmt.Print(strings.Join(toStringSlice(result), " ") + "\n")
}

func toStringSlice(slice []int) []string {
	result := make([]string, len(slice))
	for i, v := range slice {
		result[i] = strconv.Itoa(v)
	}
	return result
}