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
	n, _ := strconv.Atoi(fields[0])
	m, _ := strconv.Atoi(fields[1])

	indegree := make([]int, n)
	graph := make([][]int, n)

	for i := 0; i < m; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && line != "" {
			break
		}
		fields = strings.Fields(line)
		if len(fields) >= 2 {
			u, _ := strconv.Atoi(fields[0])
			v, _ := strconv.Atoi(fields[1])
			graph[u] = append(graph[u], v)
			indegree[v]++
		}
	}

	type entry struct {
		node   int
		order  int
	}
	priorityQueue := make([]*entry, 0, n)
	for i := 0; i < n; i++ {
		if indegree[i] == 0 {
			priorityQueue = append(priorityQueue, &entry{node: i, order: i})
		}
	}

	result := make([]int, 0, n)
	for len(priorityQueue) > 0 {
		// Find the smallest node with indegree 0
		minNode := -1
		minOrder := n + 1
		for _, e := range priorityQueue {
			if e.order < minOrder {
				minOrder = e.order
				minNode = e.node
			}
		}
		if minNode == -1 {
			break
		}

		result = append(result, minNode)
		// Remove from priority queue
		for i, e := range priorityQueue {
			if e.node == minNode {
				priorityQueue = append(priorityQueue[:i], priorityQueue[i+1:]...)
				break
			}
		}

		// Decrease indegree of neighbors
		for _, neighbor := range graph[minNode] {
			indegree[neighbor]--
			if indegree[neighbor] == 0 {
				priorityQueue = append(priorityQueue, &entry{node: neighbor, order: neighbor})
			}
		}
	}

	if len(result) != n {
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