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

	// Read N and M
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields := strings.Fields(line)
	if len(fields) < 2 {
		return
	}
	N, _ := strconv.Atoi(fields[0])
	M, _ := strconv.Atoi(fields[1])

	if N == 0 && M == 0 {
		fmt.Println("")
		return
	}

	// Adjacency list and in-degree map
	adj := make([][]int, N)
	inDegree := make([]int, N)

	for i := 0; i < M; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && line != "" {
			break
		}
		fields = strings.Fields(line)
		if len(fields) < 2 {
			continue
		}
		u, _ := strconv.Atoi(fields[0])
		v, _ := strconv.Atoi(fields[1])

		// Add edge u -> v
		adj[u] = append(adj[u], v)
		inDegree[v]++
	}

	// Kahn's algorithm with min-heap logic using sorted selection
	// Since N <= 20, we can use a simple approach: at each step, pick the smallest index node with in-degree 0

	result := make([]int, 0, N)
	available := make([]int, N)
	for i := range available {
		available[i] = -1
	}

	for len(result) < N {
		found := false
		for i := 0; i < N; i++ {
			if inDegree[i] == 0 && result[i] != true { // We need a way to track if node is processed
				// Actually, let's restructure: use a boolean array for processed nodes
				found = true
				result = append(result, i)
				inDegree[i] = -1 // mark as processed
				break
			}
		}

		if !found {
			fmt.Println("ERROR")
			return
		}

		// Update in-degrees of neighbors
		for _, v := range adj[result[len(result)-1]] {
			inDegree[v]--
		}
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