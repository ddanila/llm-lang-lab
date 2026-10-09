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
	
	// Read all input as a single string and tokenize
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	N, err := strconv.Atoi(tokens[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	
	M, err := strconv.Atoi(tokens[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	
	// Build adjacency list and in-degree count
	adj := make([][]int, N)
	inDegree := make([]int, N)
	
	idx := 2
	for i := 0; i < M; i++ {
		if idx+1 >= len(tokens) {
			break
		}
		u, err := strconv.Atoi(tokens[idx])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(tokens[idx+1])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		idx += 2
		
		// Handle self-loops and duplicate edges - they don't affect topological sort logic
		// but we need to track in-degrees correctly. Self-loops create cycles.
		if u == v {
			fmt.Println("ERROR")
			return
		}
		
		adj[u] = append(adj[u], v)
		inDegree[v]++
	}
	
	// Kahn's algorithm with a min-heap simulation using sorted list
	// Since N is small (0..20), we can use a simple approach
	
	// Find all nodes with in-degree 0
	pq := make([]int, 0)
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			pq = append(pq, i)
		}
	}
	
	// Sort pq to maintain lexicographically smallest order
	sort := func(a []int) {
		for i := 0; i < len(a); i++ {
			for j := i + 1; j < len(a); j++ {
				if a[i] > a[j] {
					a[i], a[j] = a[j], a[i]
				}
			}
		}
	}
	sort(pq)
	
	result := make([]int, 0)
	
	for len(pq) > 0 {
		// Get smallest element
		u := pq[0]
		pq = pq[1:]
		
		result = append(result, u)
		
		// Decrease in-degree of neighbors
		for _, v := range adj[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				pq = append(pq, v)
			}
		}
		sort(pq)
	}
	
	// Check if all nodes are included (cycle detection)
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