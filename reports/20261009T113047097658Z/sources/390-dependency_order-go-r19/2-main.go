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
	tokens := []string{}
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}
		tokens = append(tokens, strings.Fields(line)...)
	}

	if len(tokens) < 2 {
		fmt.Println("ERROR")
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

	if n == 0 && m == 0 {
		fmt.Println("")
		return
	}

	// Build adjacency list and in-degree map
	inDegree := make([]int, n)
	adj := make([][]int, n)

	for i := 2; i < len(tokens); i += 2 {
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

		if u < 0 || u >= n || v < 0 || v >= n {
			fmt.Println("ERROR")
			return
		}

		// Duplicate edges are allowed, so we add them anyway
		adj[u] = append(adj[u], v)
		inDegree[v]++
	}

	// Kahn's algorithm with priority: always pick smallest index node
	// Use a min-heap simulation with a sorted list since N <= 20
	priorityQueue := make([]int, 0)
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			priorityQueue = append(priorityQueue, i)
		}
	}

	// Keep priority queue sorted
	sortPriorityQueue := func() {
		// Simple insertion sort for small N
		for i := 1; i < len(priorityQueue); i++ {
			val := priorityQueue[i]
			j := i
			for j > 0 && priorityQueue[j-1] > val {
				priorityQueue[j] = priorityQueue[j-1]
				j--
			}
			priorityQueue[j] = val
		}
	}

	result := make([]string, 0, n)
	for len(result) < n {
		if len(priorityQueue) == 0 {
			fmt.Println("ERROR")
			return
		}
		sortPriorityQueue()
		node := priorityQueue[0]
		priorityQueue = priorityQueue[1:]
		result = append(result, fmt.Sprintf("%d", node))

		for _, neighbor := range adj[node] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				priorityQueue = append(priorityQueue, neighbor)
			}
		}
	}

	fmt.Print(strings.Join(result, " ") + "\n")
}