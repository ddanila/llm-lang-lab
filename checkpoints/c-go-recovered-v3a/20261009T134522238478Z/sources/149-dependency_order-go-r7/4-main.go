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
		fmt.Println("")
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

	idx := 2
	for i := 0; i < M; i++ {
		if idx+1 >= len(fields) {
			break
		}
		u, _ := strconv.Atoi(fields[idx])
		v, _ := strconv.Atoi(fields[idx+1])
		adj[u] = append(adj[u], v)
		inDegree[v]++
		idx += 2
	}

	var result []int
	available := make([]int, 0)

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

	output := strings.Join(toSlice(result), " ")
	fmt.Println(output)
}

func toSlice(s []int) []string {
	r := make([]string, len(s))
	for i, v := range s {
		r[i] = strconv.Itoa(v)
	}
	return r
}