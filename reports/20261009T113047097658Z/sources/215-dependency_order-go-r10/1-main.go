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
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields := strings.Fields(input)
	if len(fields) < 2 {
		return
	}
	N, _ := strconv.Atoi(fields[0])
	M, _ := strconv.Atoi(fields[1])

	if N == 0 && M == 0 {
		fmt.Println()
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
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		if len(parts) < 2 {
			continue
		}
		u, _ := strconv.Atoi(parts[0])
		v, _ := strconv.Atoi(parts[1])

		// Handle self-loops and duplicate edges gracefully
		if u != v {
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}

	// Kahn's algorithm with a min-heap simulation using sorted selection
	// We want lexicographically smallest ordering, so at each step we pick the smallest available node.
	
	available := []int{}
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}

	result := make([]int, 0, N)
	
	for len(result) < N {
		if len(available) == 0 {
			fmt.Println("ERROR")
			return
		}
		
		// Find the smallest node in available (since we just append sorted nodes, we can keep it sorted)
		smallest := available[0]
		for i := 1; i < len(available); i++ {
			if available[i] < smallest {
				smallest = available[i]
			}
		}
		
		result = append(result, smallest)
		
		// Remove smallest from available
		idx := -1
		for i, node := range available {
			if node == smallest {
				idx = i
				break
			}
		}
		available = append(available[:idx], available[idx+1:]...)
		
		// Update in-degrees for neighbors
		neighbors := adj[smallest]
		for _, neighbor := range neighbors {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				available = append(available, neighbor)
			}
		}
	}

	fmt.Print(result[0])
	for i := 1; i < len(result); i++ {
		fmt.Printf(" %d", result[i])
	}
	fmt.Println()
}