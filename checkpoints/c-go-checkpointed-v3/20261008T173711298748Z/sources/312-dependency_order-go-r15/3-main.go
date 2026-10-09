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

	// Build adjacency list and in-degree map from all tokens
	adj := make([][]int, N)
	inDegree := make([]int, N)

	for i := 2; i < len(tokens); i += 2 {
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
	queue := []int{}
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := []int{}
	for len(queue) > 0 {
		// Find smallest element in queue (it's already sorted if we insert in order)
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