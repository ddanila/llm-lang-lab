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
		tokens = append(tokens, strings.Fields(scanner.Text())...)
	}
	if len(tokens) == 0 {
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
		fmt.Println()
		return
	}

	inDegree := make([]int, n)
	graph := make([][]int, n)

	for i := 2; i < len(tokens); i += 2 {
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
		graph[u] = append(graph[u], v)
		inDegree[v]++
	}

	for i := range graph {
		sortGraph(i, graph[i])
	}

	queue := make([]int, 0)
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := []int{}
	for len(queue) > 0 {
		minNode := -1
		minIdx := len(queue)
		for i := 0; i < len(queue); i++ {
			if queue[i] < minNode || (minNode == -1 && i < minIdx) {
				minNode = queue[i]
				minIdx = i
			}
		}
		result = append(result, minNode)
		removed := false
		for i := 0; i < len(queue); i++ {
			if queue[i] == minNode {
				queue = append(queue[:i], queue[i+1:]...)
				removed = true
				break
			}
		}
		if !removed {
			fmt.Println("ERROR")
			return
		}

		for _, neighbor := range graph[minNode] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				queue = append(queue, neighbor)
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

func sortGraph(u int, adj []int) {
	for i := 0; i < len(adj); i++ {
		for j := i + 1; j < len(adj); j++ {
			if adj[j] < adj[i] {
				adj[i], adj[j] = adj[j], adj[i]
			}
		}
	}
}