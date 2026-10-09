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
	
	// Read all input into a single string and tokenize
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	tokens := strings.Fields(input)
	
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	M, _ := strconv.Atoi(tokens[1])
	
	// Build adjacency list and in-degree map
	adj := make([][]int, N)
	inDegree := make([]int, N)
	
	i := 2
	for i < 2+M {
		if i >= len(tokens) {
			break
		}
		u, _ := strconv.Atoi(tokens[i])
		v, _ := strconv.Atoi(tokens[i+1])
		i += 2
		
		// Handle self-loops and duplicate edges by ignoring self-loops for topological sort
		if u != v {
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}
	
	// Kahn's algorithm with a min-heap (sorted list) to get lexicographically smallest order
	minHeap := make([]int, 0)
	for i := range inDegree {
		if inDegree[i] == 0 {
			minHeap = append(minHeap, i)
		}
	}
	
	// Sort minHeap (it's a list, so we'll maintain sorted order)
	sort(minHeap)
	
	var result []int
	
	for len(minHeap) > 0 {
		// Extract minimum element
		minNode := minHeap[0]
		minHeap = minHeap[1:]
		
		result = append(result, minNode)
		
		// Process neighbors
		for _, neighbor := range adj[minNode] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				minHeap = append(minHeap, neighbor)
				sort(minHeap)
			}
		}
	}
	
	// Check if all nodes are included (i.e., no cycle)
	if len(result) != N {
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
	// Simple insertion sort for small slices
	for i := 1; i < len(slice); i++ {
		key := slice[i]
		j := i - 1
		for j >= 0 && slice[j] > key {
			slice[j+1] = slice[j]
			j--
		}
		slice[j+1] = key
	}
}