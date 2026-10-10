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
	
	// Read all input into a single string and tokenize
	input, err := reader.ReadString('\n')
	if err != nil && err != bufio.ErrNoMoreInput {
		return
	}
	
	allInput := input
	
	for {
		chunk, err := reader.ReadSlice(0)
		if err == bufio.ErrNoMoreInput {
			break
		}
		if err != nil {
			break
		}
		allInput += string(chunk)
	}
	
	tokens := strings.Fields(allInput)
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
	
	// Build adjacency list and in-degree array
	adj := make([][]int, N)
	inDegree := make([]int, N)
	
	for i := 0; i < M; i++ {
		if len(tokens) <= 2+2*i {
			break
		}
		u, err := strconv.Atoi(tokens[2+2*i])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(tokens[3+2*i])
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
	}
	
	// Kahn's algorithm with min-heap behavior using sorted queue
	available := make([]int, 0)
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}
	
	result := make([]int, 0, N)
	
	for len(available) > 0 {
		// Find the smallest node in available
		minIdx := 0
		for i := 1; i < len(available); i++ {
			if available[i] < available[minIdx] {
				minIdx = i
			}
		}
		
		minNode := available[minIdx]
		available = append(available[:minIdx], available[minIdx+1:]...)
		
		result = append(result, minNode)
		
		// Decrease in-degree of neighbors
		for _, neighbor := range adj[minNode] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				available = append(available, neighbor)
			}
		}
	}
	
	// Check if all nodes are included (cycle detection)
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