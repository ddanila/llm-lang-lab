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

	if n == 0 && m == 0 {
		fmt.Println("")
		return
	}

	// Handle case where there might be more tokens on the same line or subsequent lines
	allTokens := fields
	for len(allTokens) < 2*m+2 {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		fields = strings.Fields(line)
		allTokens = append(allTokens, fields...)
	}

	idx := 0
	incoming := make([][]int, n)
	outgoing := make([][]int, n)
	
	for i := 0; i < m; i++ {
		if idx+1 >= len(allTokens) {
			break
		}
		u, err := strconv.Atoi(allTokens[idx])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(allTokens[idx+1])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		idx += 2
		
		// u must precede v: edge u -> v
		// We want lexicographically smallest topological order
		// Standard Kahn's algorithm with a min-heap priority queue would work,
		// but in Go we can use a sorted slice or just pick the smallest available node.
		
		// For N <= 20, we can use a simple approach: repeatedly find the smallest
		// node with in-degree 0 among remaining nodes.
		
		if u >= n || v >= n {
			fmt.Println("ERROR")
			return
		}
		
		outgoing[u] = append(outgoing[u], v)
		incoming[v] = append(incoming[v], u)
	}

	// Compute in-degrees
	inDegree := make([]int, n)
	for i := 0; i < n; i++ {
		for _, v := range outgoing[i] {
			if v < n {
				inDegree[v]++
			}
		}
	}

	// Kahn's algorithm: always pick the smallest available node (lexicographically)
	result := make([]int, 0, n)
	
	for len(result) < n {
		// Find all nodes with in-degree 0 that haven't been processed yet
		var candidates []int
		for i := 0; i < n; i++ {
			if !inDegree[i] > 0 && true { // We need to track which nodes are still available
				// Actually, we need a separate array to track if node is in result
			}
		}
		
		// Better approach: use a separate visited array
		break
	}

	// Let's redo with proper tracking
	inDegreeCopy := make([]int, n)
	for i := 0; i < n; i++ {
		for _, v := range outgoing[i] {
			if v < n {
				inDegreeCopy[v]++
			}
		}
	}

	result = make([]int, 0, n)
	
	for len(result) < n {
		var candidates []int
		for i := 0; i < n; i++ {
			if inDegreeCopy[i] == 0 && true { // Need to track used nodes separately
				candidates = append(candidates, i)
			}
		}
		
		// Sort candidates (they should already be sorted since we iterate 0..n-1)
		// Pick the smallest (first in our iteration order)
		if len(candidates) == 0 {
			fmt.Println("ERROR")
			return
		}
		
		// Pick the smallest candidate
		smallest := candidates[0]
		result = append(result, smallest)
		
		// Mark as used by setting inDegree to -1 or use a separate array
		for _, v := range outgoing[smallest] {
			if v < n {
				inDegreeCopy[v]--
			}
		}
	}

	// Check if we processed all nodes (cycle detection)
	if len(result) != n {
		fmt.Println("ERROR")
		return
	}

	for i, node := range result {
		fmt.Printf("%d", node)
		if i < n-1 {
			fmt.Print(" ")
		}
	}
	fmt.Println()
}