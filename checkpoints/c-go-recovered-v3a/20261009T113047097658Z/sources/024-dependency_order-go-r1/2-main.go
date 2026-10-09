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

	// Read all input into a single string
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	// Split by whitespace
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("")
		return
	}

	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	// Handle N=0 case
	if n == 0 {
		fmt.Println("")
		return
	}

	// Build adjacency list and in-degree map
	adj := make([][]int, n)
	inDegree := make([]int, n)

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

		// Self-edges are allowed but don't affect topological sort
		// Duplicate edges are also allowed
		if u != v {
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}

	// Kahn's algorithm with a min-heap simulation using sorted list
	// For lexicographically smallest ordering, we always pick the smallest available node
	
	var queue []int
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	// Sort the initial queue to ensure lexicographically smallest order
	sort(queue)

	result := make([]int, 0, n)
	
	for len(queue) > 0 {
		// Get the smallest node (queue is kept sorted)
		u := queue[0]
		queue = queue[1:]
		
		result = append(result, u)
		
		// Process neighbors
		for _, v := range adj[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				// Insert v into sorted position
				insertSorted(queue, v)
			}
		}
	}

	// Check if all nodes were processed (i.e., no cycle)
	if len(result) != n {
		fmt.Println("ERROR")
		return
	}

	// Output result
	for i, node := range result {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(node)
	}
	fmt.Println()
}

func sort(slice []int) {
	// Simple bubble sort for small slices
	n := len(slice)
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			if slice[j] > slice[j+1] {
				slice[j], slice[j+1] = slice[j+1], slice[j]
			}
		}
	}
}

func insertSorted(slice []int, val int) {
	n := len(slice)
	for i := 0; i < n; i++ {
		if slice[i] > val {
			// Insert at position i
			newSlice := make([]int, n+1)
			copy(newSlice, slice[:i])
			newSlice[i] = val
			copy(newSlice[i+1:], slice[i:])
			slice = newSlice
			return
		}
	}
	// Append to end if all elements are smaller or equal
	slice = append(slice, val)
}