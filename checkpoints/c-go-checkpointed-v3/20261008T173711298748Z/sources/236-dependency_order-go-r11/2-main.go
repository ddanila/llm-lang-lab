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
	
	// Read all input
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	fields := strings.Fields(input)
	if len(fields) < 2 {
		fmt.Println("ERROR")
		return
	}
	
	N, _ := strconv.Atoi(fields[0])
	M, _ := strconv.Atoi(fields[1])
	
	// Handle N=0 case
	if N == 0 {
		fmt.Println("")
		return
	}
	
	// Adjacency list and in-degree map
	adj := make([][]int, N)
	inDegree := make([]int, N)
	
	// Read M edges
	for i := 0; i < M; i++ {
		line, _ := reader.ReadString('\n')
		fields = strings.Fields(line)
		if len(fields) >= 2 {
			u, _ := strconv.Atoi(fields[0])
			v, _ := strconv.Atoi(fields[1])
			if u >= 0 && u < N && v >= 0 && v < N {
				adj[u] = append(adj[u], v)
				inDegree[v]++
			}
		}
	}
	
	// Kahn's algorithm with lexicographically smallest ordering
	visited := make([]bool, N)
	result := make([]int, 0, N)
	
	for len(result) < N {
		var bestNode int = -1
		
		// Find all nodes with in-degree 0 that haven't been processed yet
		for i := 0; i < N; i++ {
			if !visited[i] && inDegree[i] == 0 {
				if bestNode == -1 || i < bestNode {
					bestNode = i
				}
			}
		}
		
		if bestNode == -1 {
			// No node with in-degree 0, cycle detected
			fmt.Println("ERROR")
			return
		}
		
		result = append(result, bestNode)
		visited[bestNode] = true
		
		// Decrease in-degree of neighbors
		for _, neighbor := range adj[bestNode] {
			inDegree[neighbor]--
		}
	}
	
	fmt.Print(strings.Join(toStrings(result), " ") + "\n")
}

func toStrings(slice []int) []string {
	result := make([]string, len(slice))
	for i, v := range slice {
		result[i] = strconv.Itoa(v)
	}
	return result
}