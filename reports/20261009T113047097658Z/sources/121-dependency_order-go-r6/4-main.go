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
		fmt.Println("")
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
		
		adj[u] = append(adj[u], v)
		inDegree[v]++
	}
	
	// Kahn's algorithm with min-heap simulation
	result := make([]int, 0, N)
	available := make([]int, 0)
	
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}
	
	// Use a min-heap approach: always pick smallest available node
	// Sort initially
	for i := 0; i < len(available)-1; i++ {
		for j := i + 1; j < len(available); j++ {
			if available[j] < available[i] {
				available[i], available[j] = available[j], available[i]
			}
		}
	}
	
	for len(result) < N {
		if len(available) == 0 {
			fmt.Println("ERROR")
			return
		}
		
		u := available[0]
		available = available[1:]
		
		result = append(result, u)
		
		for _, v := range adj[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				available = append(available, v)
			}
		}
		
		// Re-sort to maintain min-heap property
		for i := 0; i < len(available)-1; i++ {
			for j := i + 1; j < len(available); j++ {
				if available[j] < available[i] {
					available[i], available[j] = available[j], available[i]
				}
			}
		}
	}
	
	output := make([]string, N)
	for i, v := range result {
		output[i] = strconv.Itoa(v)
	}
	fmt.Print(strings.Join(output, " "))
	fmt.Println()
}