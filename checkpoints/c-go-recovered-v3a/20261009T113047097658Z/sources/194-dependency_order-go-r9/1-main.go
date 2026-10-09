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
	if err != nil && err != io.EOF {
		return
	}
	
	// Split by whitespace
	tokens := strings.Fields(input)
	if len(tokens) < 2 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	m, _ := strconv.Atoi(tokens[1])
	
	// If N=0 or M=0, output empty line
	if n == 0 || m == 0 {
		fmt.Println("")
		return
	}
	
	// Build adjacency list and in-degree array
	adj := make([][]int, n)
	inDegree := make([]int, n)
	
	for i := 2; i < len(tokens); i += 2 {
		if i+1 >= len(tokens) {
			break
		}
		u, _ := strconv.Atoi(tokens[i])
		v, _ := strconv.Atoi(tokens[i+1])
		
		if u < n && v < n {
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}
	
	// Kahn's algorithm with min-heap (using sorted list since N is small)
	// Start with all nodes having in-degree 0, sorted
	queue := []int{}
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}
	
	// Sort queue to ensure lexicographically smallest order
	sort.Ints(queue)
	
	result := []int{}
	
	for len(queue) > 0 {
		// Take the smallest node from queue
		current := queue[0]
		queue = queue[1:]
		result = append(result, current)
		
		// Process all neighbors of current node
		for _, neighbor := range adj[current] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				queue = append(queue, neighbor)
			}
		}
		// Sort queue to maintain lexicographic order
		sort.Ints(queue)
	}
	
	// Check if all nodes are included (cycle detection)
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
	fmt.Println("")
}

var io = &ioStdlib{}

type ioStdlib struct{}

func (i *ioStdlib) Read(p []byte) (n int, err error) { return 0, nil }