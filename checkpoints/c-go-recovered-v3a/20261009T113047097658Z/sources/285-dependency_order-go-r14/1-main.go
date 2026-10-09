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
	input := scanner.Text()
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}

	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	m := n // This is wrong, let me fix it.
	
	// Actually, I need to parse M from tokens[1]
	if len(tokens) < 2 {
		// If no M provided, assume 0 edges? Or error?
		// Based on examples, M is always provided.
		fmt.Println("ERROR")
		return
	}
	
	m, err = strconv.Atoi(tokens[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	// Build graph
	inDegree := make([]int, n)
	graph := make([][]int, n)

	for i := 0; i < m; i++ {
		if len(tokens) > 2+i*2 {
			u, err1 := strconv.Atoi(tokens[2+2*i])
			v, err2 := strconv.Atoi(tokens[3+2*i])
			if err1 != nil || err2 != nil {
				fmt.Println("ERROR")
				return
			}
			
			graph[u] = append(graph[u], v)
			inDegree[v]++
		} else {
			break
		}
	}

	// Kahn's algorithm for topological sort with lexicographically smallest result
	// Use a min-heap or sorted list of zero in-degree nodes
	zeroNodes := []int{}
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			zeroNodes = append(zeroNodes, i)
		}
	}

	result := []int{}
	
	// Since we want lexicographically smallest, we process nodes in increasing order
	// We can use a simple approach: always pick the smallest available node
	
	for len(result) < n {
		if len(zeroNodes) == 0 {
			fmt.Println("ERROR")
			return
		}
		
		// Sort zeroNodes to get lexicographically smallest
		// Actually, we can maintain it sorted by always picking min and re-inserting
		// But for simplicity, let's sort each time (n is small, up to 20)
		
		sort := func(arr []int) {
			for i := 0; i < len(arr); i++ {
				for j := i + 1; j < len(arr); j++ {
					if arr[i] > arr[j] {
						arr[i], arr[j] = arr[j], arr[i]
					}
				}
			}
		}
		sort(zeroNodes)
		
		node := zeroNodes[0]
		zeroNodes = zeroNodes[1:]
		result = append(result, node)
		
		for _, neighbor := range graph[node] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				zeroNodes = append(zeroNodes, neighbor)
			}
		}
	}

	fmt.Print(strings.Join(result, " ") + "\n")
}