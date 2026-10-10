package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	// Read all stdin
	data, err := os.Stdin.ReadAll()
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	
	tokens := strings.Fields(string(data))
	
	if len(tokens) == 0 {
		fmt.Println("")
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	M, _ := strconv.Atoi(tokens[1])
	
	// Handle N=0 case
	if N == 0 {
		fmt.Println("")
		return
	}
	
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
		
		// Handle self-loops by ignoring them
		if u != v && u < N && v < N {
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}
	
	// Kahn's algorithm with min-heap approach
	minHeap := make([]int, 0)
	for i := range inDegree {
		if inDegree[i] == 0 {
			minHeap = append(minHeap, i)
		}
	}
	
	sort(minHeap)
	
	var result []int
	
	for len(minHeap) > 0 {
		minNode := minHeap[0]
		minHeap = minHeap[1:]
		
		result = append(result, minNode)
		
		for _, neighbor := range adj[minNode] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				minHeap = append(minHeap, neighbor)
				sort(minHeap)
			}
		}
	}
	
	if len(result) != N {
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

func sort(slice []int) {
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