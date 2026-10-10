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
	fields := strings.Fields(input)

	if len(fields) < 2 {
		fmt.Println("ERROR")
		return
	}

	n, err := strconv.Atoi(fields[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	m, err := strconv.Atoi(fields[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	// Handle N=0 case
	if n == 0 {
		fmt.Println("")
		return
	}

	// Build graph
	inDegree := make([]int, n)
	graph := make([][]int, n)

	for i := 0; i < m; i++ {
		if len(fields) > 2+i*2 {
			u, err := strconv.Atoi(fields[2+i*2])
			if err != nil {
				fmt.Println("ERROR")
				return
			}
			v, err := strconv.Atoi(fields[3+i*2])
			if err != nil {
				fmt.Println("ERROR")
				return
			}

			if u >= n || v >= n {
				fmt.Println("ERROR")
				return
			}

			graph[u] = append(graph[u], v)
			inDegree[v]++
		}
	}

	// Kahn's algorithm with a min-heap simulation using sorted queue
	// To get lexicographically smallest order, we always pick the smallest available node
	queue := make([]int, 0)
	result := make([]int, 0)

	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	// Sort queue initially (though they are already in order since we iterate 0..n-1)
	// But as we pop from the front and push to back, we need to keep it sorted
	// Since we always want the smallest available node, we use a min-heap approach
	// But for simplicity with Go, we can use a sorted slice and binary search insertion

	for len(queue) > 0 {
		// Find the smallest element in queue (it's already sorted if we maintain order)
		// Actually, when we insert new nodes, they might not be in order, so we need to sort
		// Let's just use a simple approach: keep queue sorted

		// Get the first (smallest) element
		u := queue[0]
		queue = queue[1:]

		result = append(result, u)

		// Process neighbors
		for _, v := range graph[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				// Insert v into queue in sorted order
				insertIndex := -1
				for i := 0; i < len(queue); i++ {
					if queue[i] > v {
						insertIndex = i
						break
					}
				}
				if insertIndex == -1 {
					insertIndex = len(queue)
				}
				queue = append(queue, 0) // placeholder
				copy(queue[insertIndex+1:], queue[insertIndex:])
				queue[insertIndex] = v
			}
		}
	}

	if len(result) != n {
		fmt.Println("ERROR")
		return
	}

	fmt.Print(strings.Join(toStringSlice(result), " ") + "\n")
}

func toStringSlice(slice []int) []string {
	result := make([]string, len(slice))
	for i, v := range slice {
		result[i] = strconv.Itoa(v)
	}
	return result
}