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
	var tokens []string
	for scanner.Scan() {
		tokens = append(tokens, strings.Fields(scanner.Text())...)
	}

	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}

	n, err := strconv.Atoi(tokens[0])
	if err != nil || n < 0 || n > 20 {
		fmt.Println("ERROR")
		return
	}

	mStr := ""
	if len(tokens) > 1 {
		mStr = tokens[1]
	}
	m, err := strconv.Atoi(mStr)
	if err != nil || m < 0 || m > 100 {
		fmt.Println("ERROR")
		return
	}

	// Parse edges
	indegree := make([]int, n)
	adj := make([][]int, n)

	for i := 2; i < len(tokens); i += 2 {
		if i+1 >= len(tokens) {
			break
		}
		u, err := strconv.Atoi(tokens[i])
		if err != nil || u < 0 || u >= n {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(tokens[i+1])
		if err != nil || v < 0 || v >= n {
			fmt.Println("ERROR")
			return
		}
		// u -> v means u must precede v
		adj[u] = append(adj[u], v)
		indegree[v]++
	}

	// Kahn's algorithm with min-heap simulation using sorted queue
	// To get lexicographically smallest, we always pick the smallest available node
	queue := make([]int, 0)
	for i := 0; i < n; i++ {
		if indegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := make([]int, 0, n)
	idx := 0
	for len(queue) > 0 {
		// Find the smallest element in queue (it's already sorted if we insert in order)
		minNode := queue[0]
		queue = queue[1:]
		result = append(result, minNode)

		for _, neighbor := range adj[minNode] {
			indegree[neighbor]--
			if indegree[neighbor] == 0 {
				// Insert in sorted order
				// Binary search for insertion point
				insertIdx := -1
				for j := 0; j < len(queue); j++ {
					if queue[j] > neighbor {
						insertIdx = j
						break
					}
				}
				if insertIdx == -1 {
					insertIdx = len(queue)
				}
				queue = append(queue, 0) // placeholder
				copy(queue[insertIdx+1:], queue[insertIdx:])
				queue[insertIdx] = neighbor
			}
		}
	}

	if len(result) != n {
		fmt.Println("ERROR")
		return
	}

	fmt.Print(strings.Join(ToStringSlice(result), " ") + "\n")
}

func ToStringSlice(slice []int) []string {
	result := make([]string, len(slice))
	for i, v := range slice {
		result[i] = strconv.Itoa(v)
	}
	return result
}