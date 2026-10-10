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
	
	// Read all lines
	var allLines []string
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		allLines = append(allLines, line)
	}
	
	// Combine all lines and split into tokens
	var allTokens []string
	for _, line := range allLines {
		fields := strings.Fields(line)
		allTokens = append(allTokens, fields...)
	}
	
	if len(allTokens) < 2 {
		fmt.Println("ERROR")
		return
	}

	n, err := strconv.Atoi(allTokens[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	m, err := strconv.Atoi(allTokens[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	if n == 0 && m == 0 {
		fmt.Println("")
		return
	}

	outgoing := make([][]int, n)
	
	for i := 0; i < m; i++ {
		idx := 2 + 2*i
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
		
		if u >= n || v >= n {
			fmt.Println("ERROR")
			return
		}
		
		outgoing[u] = append(outgoing[u], v)
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
		var candidates []int
		for i := 0; i < n; i++ {
			if inDegree[i] == 0 {
				candidates = append(candidates, i)
			}
		}
		
		if len(candidates) == 0 {
			fmt.Println("ERROR")
			return
		}
		
		// Pick the smallest candidate (first one since we iterate in order)
		smallest := candidates[0]
		result = append(result, smallest)
		
		// Decrease in-degree of neighbors
		for _, v := range outgoing[smallest] {
			if v < n {
				inDegree[v]--
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