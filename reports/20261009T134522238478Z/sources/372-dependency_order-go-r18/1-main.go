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
	if !scanner.Scan() {
		return
	}
	tokens := strings.Fields(scanner.Text())
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
		fmt.Println()
		return
	}

	inDegree := make([]int, n)
	graph := make([][]int, n)
	for i := range graph {
		graph[i] = nil
	}

	edgesRead := 0
	for edgesRead < m {
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		fields := strings.Fields(line)
		for len(fields) >= 2 {
			u, err1 := strconv.Atoi(fields[0])
			v, err2 := strconv.Atoi(fields[1])
			if err1 != nil || err2 != nil {
				break
			}
			graph[u] = append(graph[u], v)
			inDegree[v]++
			edgesRead++
			fields = fields[2:]
		}
	}

	// Kahn's algorithm with min-heap simulation using sorted adjacency
	// To get lexicographically smallest ordering, we always pick the smallest available node.
	available := make([]int, 0)
	for i := range inDegree {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}

	result := make([]int, 0, n)
	idx := 0
	for len(result) < n && idx < len(available) {
		// available is kept sorted; if we pop smallest and insert larger nodes, keep sorted.
		minNode := available[idx]
		result = append(result, minNode)

		// Remove minNode from available
		available = append(available[:idx], available[idx+1:]...)

		// Process neighbors of minNode
		for _, neighbor := range graph[minNode] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				// Insert into sorted position
				i := idx
				for i < len(available) && available[i] < neighbor {
					i++
				}
				available = append(available[:i], append([]int{neighbor}, available[i:]...)...)
			}
		}

		// Re-sort remaining available to ensure smallest first (already sorted by insertion logic, but safe)
		if len(available) > 0 {
			// Quick sort using simple bubble for small slices
			for i := 0; i < len(available)-1; i++ {
				for j := 0; j < len(available)-i-1; j++ {
					if available[j] > available[j+1] {
						available[j], available[j+1] = available[j+1], available[j]
					}
				}
			}
		}
	}

	if len(result) != n {
		fmt.Println("ERROR")
		return
	}

	for i, v := range result {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(v)
	}
	fmt.Println()
}