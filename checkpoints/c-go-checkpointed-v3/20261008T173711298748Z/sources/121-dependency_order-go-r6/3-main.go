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
	
	// Read all input into a single string
	input, _ := reader.ReadString('\n')
	
	// Split into tokens
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	N, err1 := strconv.Atoi(tokens[0])
	M, err2 := strconv.Atoi(tokens[1])
	if err1 != nil || err2 != nil {
		fmt.Println("ERROR")
		return
	}
	
	if N == 0 && M == 0 {
		fmt.Println("")
		return
	}
	
	// Build adjacency list and in-degree count
	adj := make([][]int, N)
	inDegree := make([]int, N)
	
	for i := 2; i < len(tokens); i += 2 {
		u, err3 := strconv.Atoi(tokens[i])
		if err3 != nil {
			fmt.Println("ERROR")
			return
		}
		
		v, err4 := strconv.Atoi(tokens[i+1])
		if err4 != nil {
			fmt.Println("ERROR")
			return
		}
		
		// Add edge u -> v
		adj[u] = append(adj[u], v)
		inDegree[v]++
	}
	
	// Kahn's algorithm with lexicographically smallest ordering
	result := make([]int, 0, N)
	available := make([]int, 0)
	
	// Initialize with nodes having in-degree 0
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}
	
	// Sort available to always pick smallest first
	sortAvailable := func() {
		for i := 0; i < len(available)-1; i++ {
			for j := i + 1; j < len(available); j++ {
				if available[j] < available[i] {
					available[i], available[j] = available[j], available[i]
				}
			}
		}
	}
	sortAvailable()
	
	for len(result) < N {
		if len(available) == 0 {
			// Cycle detected - not all nodes can be processed
			fmt.Println("ERROR")
			return
		}
		
		// Pick the smallest available node
		u := available[0]
		available = available[1:]
		
		result = append(result, u)
		
		// Update in-degrees and add newly available nodes
		for _, v := range adj[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				available = append(available, v)
			}
		}
		
		sortAvailable()
	}
	
	fmt.Print(strings.Join(convertIntsToString(result), " "))
	fmt.Println()
}

func convertIntsToString(intSlice []int) []string {
	result := make([]string, len(intSlice))
	for i, v := range intSlice {
		result[i] = strconv.Itoa(v)
	}
	return result
}