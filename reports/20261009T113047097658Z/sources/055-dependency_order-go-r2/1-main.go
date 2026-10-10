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

	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	m, err := strconv.Atoi(tokens[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	// Build graph and in-degree count
	inDegree := make([]int, n)
	adj := make([][]int, n)

	for i := 0; i < m; i++ {
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

		// Self-edges are allowed but don't affect topological order (u precedes u)
		// Duplicate edges: we still need to count them for in-degree if they matter
		// For lexicographically smallest ordering, we process each edge.
		// However, duplicate edges would cause double counting of in-degree which is wrong.
		// The problem says "Duplicate edges and self-edges are allowed" - this means
		// the input may contain them, but for topological sort, multiple identical edges
		// should not increase in-degree multiple times. We'll use a set-like approach
		// by checking adjacency before adding to avoid double counting.

		if u < n && v < n {
			// Check if edge already exists to avoid double counting in-degree
			exists := false
			for _, neighbor := range adj[u] {
				if neighbor == v {
					exists = true
					break
				}
			}
			if !exists {
				adj[u] = append(adj[u], v)
				inDegree[v]++
			}
		}
	}

	// Kahn's algorithm with min-heap simulation using sorted queue
	// For lexicographically smallest, we always pick the smallest available node
	queue := make([]int, 0)
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := make([]int, 0, n)
	idx := 0

	for len(queue) > 0 {
		// Sort queue to always pick smallest (since we may add nodes in any order)
		// But to keep it efficient, we can just sort each time or use a min-heap
		// Since N <= 20, sorting is fine
		for i := 1; i < len(queue); i++ {
			if queue[i] < queue[i-1] {
				queue[i], queue[i-1] = queue[i-1], queue[i]
			}
		}

		// Pick the smallest (now at index 0)
		smallest := queue[0]
		queue = append(queue[:0], queue[1:]...)
		result = append(result, smallest)

		for _, neighbor := range adj[smallest] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				queue = append(queue, neighbor)
			}
		}
	}

	if len(result) != n {
		fmt.Println("ERROR")
	} else {
		fmt.Print(strings.Join(convertIntsToStrings(result), " "))
		fmt.Println()
	}
}

func convertIntsToStrings(ints []int) []string {
	result := make([]string, len(ints))
	for i, v := range ints {
		result[i] = strconv.Itoa(v)
	}
	return result
}