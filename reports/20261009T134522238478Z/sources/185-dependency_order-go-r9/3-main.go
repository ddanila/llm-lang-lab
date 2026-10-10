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
		fmt.Println("ERROR")
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

	if N == 0 && M == 0 {
		fmt.Println("")
		return
	}

	// Build adjacency list and in-degree map
	adj := make([][]int, N)
	inDegree := make([]int, N)

	for i := 0; i < len(tokens)-1; i += 2 {
		if i+1 >= len(tokens) {
			break
		}
		u, err := strconv.Atoi(tokens[i])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(tokens[i+1])
		if err != nil {
			fmt.Println("ERROR")
			return
		}

		// Self-edges are allowed but don't affect topological sort order (u must precede u)
		// Duplicate edges: we need to handle them correctly. Since we're using in-degree,
		// duplicate edges from u to v should increment inDegree[v] multiple times.
		if u != v && u >= 0 && u < N && v >= 0 && v < N {
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}

	// Kahn's algorithm with a min-heap (using sorted slice as heap)
	// For lexicographically smallest ordering, we always pick the smallest available node
	available := []int{}
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}

	// Sort available to start with smallest
	sortInts(available)

	result := []int{}

	for len(result) < N {
		if len(available) == 0 {
			fmt.Println("ERROR")
			return
		}

		// Pick the smallest node
		u := available[0]
		available = available[1:]
		result = append(result, u)

		// Process neighbors
		for _, v := range adj[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				available = append(available, v)
			}
		}

		// Sort available to maintain lexicographical order
		sortInts(available)
	}

	// Check if we got a valid topological ordering (no cycle detected)
	if len(result) != N {
		fmt.Println("ERROR")
		return
	}

	fmt.Print(strings.Join(formatInts(result), " ") + "\n")
}

func sortInts(arr []int) {
	for i := 0; i < len(arr)-1; i++ {
		for j := i + 1; j < len(arr); j++ {
			if arr[j] < arr[i] {
				arr[i], arr[j] = arr[j], arr[i]
			}
		}
	}
}

func formatInts(arr []int) []string {
	result := make([]string, len(arr))
	for i, v := range arr {
		result[i] = strconv.Itoa(v)
	}
	return result
}