package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read all input as a single tokenized stream
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	
	if len(tokens) == 0 {
		fmt.Println("")
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
	
	// For N=0, output empty line
	if N == 0 {
		fmt.Println("")
		return
	}
	
	// Build adjacency list and in-degree map
	adj := make([][]int, N)
	inDegree := make([]int, N)
	
	for i := 2; i < len(tokens) && i < 2+M; i++ {
		uStr := tokens[i]
		vStr := tokens[i+1]
		i += 2
		
		u, _ := strconv.Atoi(uStr)
		v, _ := strconv.Atoi(vStr)
		
		if u >= N || v >= N {
			fmt.Println("ERROR")
			return
		}
		
		adj[u] = append(adj[u], v)
		inDegree[v]++
	}
	
	// Kahn's algorithm with sorted available nodes
	available := []int{}
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}
	sort.Slice(available, func(i, j int) bool {
		return available[i] < available[j]
	})
	
	result := []int{}
	
	for len(result) < N {
		if len(available) == 0 {
			fmt.Println("ERROR")
			return
		}
		
		// Pick the smallest node
		node := available[0]
		available = available[1:]
		
		result = append(result, node)
		
		// Process neighbors
		for _, neighbor := range adj[node] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				// Insert in sorted order using binary search
				idx := sort.Search(available, func(i int) bool {
					return available[i] >= neighbor
				})
				available = append(available, 0)
				copy(available[idx+1:], available[idx:])
				available[idx] = neighbor
			}
		}
		
		sort.Slice(available, func(i, j int) bool {
			return available[i] < available[j]
		})
	}
	
	// Check if all nodes were processed (no cycle)
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