package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	input := scanner.Text()
	fields := strings.Fields(input)

	if len(fields) == 0 {
		fmt.Println("ERROR")
		return
	}

	N, _ := strconv.Atoi(fields[0])
	M, _ := strconv.Atoi(fields[1])

	if N == 0 {
		fmt.Println("")
		return
	}

	adj := make([][]int, N)
	inDegree := make([]int, N)

	for i := 0; i < M; i++ {
		if i+2 >= len(fields) {
			break
		}
		u, _ := strconv.Atoi(fields[i+2])
		v, _ := strconv.Atoi(fields[i+3])
		adj[u] = append(adj[u], v)
		inDegree[v]++
		i += 3
	}

	// Use a min-heap approach with a sorted list of zero in-degree nodes
	type node struct {
		val int
	}

	// For N <= 20, we can use a simple slice and sort each time to find the smallest available node
	var result []int
	available := make([]int, N)
	copy(available, inDegree) // We'll track in-degree separately

	// Re-compute available nodes (those with inDegree == 0)
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}

	// We need to maintain a sorted list of available nodes
	sortAvailable := func() []int {
		sorted := make([]int, len(available))
		copy(sorted, available)
		for i := 0; i < len(sorted); i++ {
			for j := i + 1; j < len(sorted); j++ {
				if sorted[j] < sorted[i] {
					sorted[i], sorted[j] = sorted[j], sorted[i]
				}
			}
		}
		return sorted
	}

	available = sortAvailable()

	for len(result) < N {
		if len(available) == 0 {
			fmt.Println("ERROR")
			return
		}
		node := available[0] // Smallest index node with inDegree 0
		result = append(result, node)

		// Remove this node from available and update in-degrees
		for i := 0; i < len(available); i++ {
			if available[i] == node {
				available = append(available[:i], available[i+1:]...)
				break
			}
		}

		// Decrease in-degree of neighbors
		for _, neighbor := range adj[node] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				available = append(available, neighbor)
			}
		}

		// Keep available sorted
		sortAvailable()
	}

	fmt.Println(strings.Join(toString(result), " "))
}

func toString(s []int) []string {
	r := make([]string, len(s))
	for i, v := range s {
		r[i] = strconv.Itoa(v)
	}
	return r
}