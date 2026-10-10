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
	input := scanner.Text()
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

	m := 0
	if len(tokens) >= 2 {
		var err error
		m, err = strconv.Atoi(tokens[1])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
	}

	// Handle N=0 case
	if n == 0 {
		fmt.Println("")
		return
	}

	// Build graph
	inDegree := make([]int, n)
	graph := make([][]int, n)

	for i := 0; i < m; i++ {
		if len(tokens) > 2+i*2 {
			u, err1 := strconv.Atoi(tokens[2+2*i])
			v, err2 := strconv.Atoi(tokens[3+2*i])
			if err1 != nil || err2 != nil {
				fmt.Println("ERROR")
				return
			}
			
			graph[u] = append(graph[u], v)
			inDegree[v]++
		} else {
			break
		}
	}

	// Kahn's algorithm for topological sort with lexicographically smallest result
	zeroNodes := []int{}
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			zeroNodes = append(zeroNodes, i)
		}
	}

	result := []int{}
	
	for len(result) < n {
		if len(zeroNodes) == 0 {
			fmt.Println("ERROR")
			return
		}
		
		// Sort zeroNodes to get lexicographically smallest
		sort := func(arr []int) {
			for i := 0; i < len(arr); i++ {
				for j := i + 1; j < len(arr); j++ {
					if arr[i] > arr[j] {
						arr[i], arr[j] = arr[j], arr[i]
					}
				}
			}
		}
		sort(zeroNodes)
		
		node := zeroNodes[0]
		zeroNodes = zeroNodes[1:]
		result = append(result, node)
		
		for _, neighbor := range graph[node] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				zeroNodes = append(zeroNodes, neighbor)
			}
		}
	}

	fmt.Print(strings.Join(resultToStrings(result), " ") + "\n")
}

func resultToStrings(result []int) []string {
	strs := make([]string, len(result))
	for i, v := range result {
		strs[i] = strconv.Itoa(v)
	}
	return strs
}