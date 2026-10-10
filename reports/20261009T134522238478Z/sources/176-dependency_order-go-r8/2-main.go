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

	// Read all input
	var sb strings.Builder
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		sb.WriteString(line)
	}
	input := sb.String()
	
	// Split by whitespace
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

	// Build adjacency list and in-degree map
	adj := make([][]int, N)
	inDegree := make([]int, N)

	for i := 0; i < M; i++ {
		if i+2 >= len(tokens) {
			break
		}
		u, err3 := strconv.Atoi(tokens[i+2])
		v, err4 := strconv.Atoi(tokens[i+3])
		if err3 != nil || err4 != nil {
			fmt.Println("ERROR")
			return
		}

		adj[u] = append(adj[u], v)
		inDegree[v]++
	}

	// Kahn's algorithm
	available := []int{}
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}

	result := []int{}

	for len(result) < N {
		if len(available) == 0 {
			fmt.Println("ERROR")
			return
		}

		// Sort available to get lexicographically smallest (bubble sort for small N)
		for i := 0; i < len(available); i++ {
			for j := i + 1; j < len(available); j++ {
				if available[j] < available[i] {
					available[i], available[j] = available[j], available[i]
				}
			}
		}

		// Take the smallest node
		u := available[0]
		available = available[1:]
		result = append(result, u)

		// Update in-degrees
		for _, v := range adj[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				available = append(available, v)
			}
		}
	}

	// Check if we processed all nodes (i.e., no cycle)
	if len(result) != N {
		fmt.Println("ERROR")
		return
	}

	for i, node := range result {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(node)
	}
	fmt.Println()
}