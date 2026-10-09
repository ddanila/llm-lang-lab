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

	if len(tokens) > 1 {
		M, _ := strconv.Atoi(tokens[1])
		for i := 2; i < len(tokens); i += 2 {
			u, _ := strconv.Atoi(tokens[i])
			v, _ := strconv.Atoi(tokens[i+1])
			// Process edge u -> v
		}
	}

	// Build adjacency list and in-degree map
	adj := make([][]int, N)
	inDegree := make([]int, N)

	for i := 0; i < len(tokens); i += 2 {
		if i+1 >= len(tokens) {
			break
		}
		u, _ := strconv.Atoi(tokens[i])
		v, _ := strconv.Atoi(tokens[i+1])
		if u < N && v < N {
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}

	// Kahn's algorithm with min-heap simulation using sorted selection
	// To get lexicographically smallest, we always pick the smallest available node
	queue := []int{}
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := []int{}
	idx := 0
	for len(queue) > 0 {
		// Find smallest element in queue (it's already sorted if we insert in order)
		// But we need to maintain sorted order. Let's use a simple approach:
		// Keep queue sorted by inserting in order and picking first
		smallest := queue[0]
		queue = queue[1:]
		result = append(result, smallest)

		for _, neighbor := range adj[smallest] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				// Insert in sorted order
				insertPos := len(queue)
				for i := range queue {
					if queue[i] > neighbor {
						insertPos = i
						break
					}
				}
				queue = append(queue[:insertPos], append([]int{neighbor}, queue[insertPos:]...)...)
			}
		}
	}

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