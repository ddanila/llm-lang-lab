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
	
	in := make([][]int, N)  // in[v] contains list of nodes that point to v
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
	}
	
	// Compute in-degrees
	inDegree := make([]int, N)
	for i := 0; i < N; i++ {
		for _, pred := range in[i] {
			inDegree[i]++
		}
	}
	
	// Kahn's algorithm with always picking smallest available node
	available := make([]int, 0, N)
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			available = append(available, i)
		}
	}
	
	result := make([]int, 0, N)
	
	for len(available) > 0 {
		// Find the smallest node in available (linear scan is fine for N <= 20)
		minIdx := 0
		for i := 1; i < len(available); i++ {
			if available[i] < available[minIdx] {
				minIdx = i
			}
		}
		
		minNode := available[minIdx]
		available = append(available[:minIdx], available[minIdx+1:]...)
		
		result = append(result, minNode)
		
		// For each node that points to minNode, decrease its in-degree
		for _, pred := range in[minNode] {
			inDegree[pred]--
			if inDegree[pred] == 0 {
				available = append(available, pred)
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