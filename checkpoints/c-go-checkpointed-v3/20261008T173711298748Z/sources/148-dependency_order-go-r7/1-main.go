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
	var input strings.Builder
	for scanner.Scan() {
		input.WriteString(scanner.Text())
		input.WriteString(" ")
	}
	
	parts := strings.Fields(input.String())
	if len(parts) < 2 {
		fmt.Println("ERROR")
		return
	}
	
	N, err := strconv.Atoi(parts[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	
	M, err := strconv.Atoi(parts[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	
	in := make([][]int, N)
	outDegree := make([]int, N)
	for i := 0; i < M; i++ {
		if len(parts) <= 2+2*i {
			break
		}
		u, err := strconv.Atoi(parts[2+2*i])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(parts[3+2*i])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		
		if u < 0 || u >= N || v < 0 || v >= N {
			fmt.Println("ERROR")
			return
		}
		
		in[v] = append(in[v], u)
		outDegree[u]++
	}
	
	// Kahn's algorithm with min-heap simulation using sorted adjacency
	// To get lexicographically smallest ordering, we always pick the smallest available node
	
	available := make([]int, 0, N)
	for i := 0; i < N; i++ {
		if outDegree[i] == 0 {
			available = append(available, i)
		}
	}
	
	result := make([]int, 0, N)
	
	for len(available) > 0 {
		// Find the smallest node in available
		minIdx := 0
		for i := 1; i < len(available); i++ {
			if available[i] < available[minIdx] {
				minIdx = i
			}
		}
		
		minNode := available[minIdx]
		available = append(available[:minIdx], available[minIdx+1:]...)
		
		result = append(result, minNode)
		
		// Update out degrees and add new available nodes
		for _, neighbor := range in[minNode] {
			outDegree[neighbor]--
			if outDegree[neighbor] == 0 {
				available = append(available, neighbor)
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