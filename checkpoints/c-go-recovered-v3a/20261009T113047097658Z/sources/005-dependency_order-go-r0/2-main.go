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

	// Kahn's algorithm: at each step pick smallest index node with in-degree 0
	result := make([]int, 0, N)
	processed := make([]bool, N)

	for len(result) < N {
		found := -1
		// Find the smallest index node with in-degree 0 that hasn't been processed
		for i := 0; i < N; i++ {
			if !processed[i] && inDegree[i] == 0 {
				found = i
				break
			}
		}

		if found == -1 {
			fmt.Println("ERROR")
			return
		}

		result = append(result, found)
		processed[found] = true

		// Update in-degrees of neighbors
		for _, v := range adj[found] {
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