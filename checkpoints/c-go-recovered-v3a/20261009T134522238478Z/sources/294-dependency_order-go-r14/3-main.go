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
	if err != nil && err != bufio.ErrNoMoreInput {
		return
	}
	
	tokens := strings.Fields(input)
	if len(tokens) < 2 {
		fmt.Println("ERROR")
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	M, _ := strconv.Atoi(tokens[1])
	
	indegree := make([]int, N)
	graph := make([][]int, N)
	
	idx := 2
	for i := 0; i < M; i++ {
		if idx+1 >= len(tokens) {
			break
		}
		u, _ := strconv.Atoi(tokens[idx])
		v, _ := strconv.Atoi(tokens[idx+1])
		idx += 2
		
		graph[u] = append(graph[u], v)
		indegree[v]++
	}
	
	queue := make([]int, 0)
	for i := 0; i < N; i++ {
		if indegree[i] == 0 {
			queue = append(queue, i)
		}
	}
	
	result := []int{}
	
	for len(queue) > 0 {
		// Find the smallest index in queue (lexicographically smallest)
		minIdx := -1
		minVal := N + 1
		
		for i, val := range queue {
			if val < minVal {
				minVal = val
				minIdx = i
			}
		}
		
		if minIdx == -1 {
			break
		}
		
		u := queue[minIdx]
		queue = append(queue[:minIdx], queue[minIdx+1:]...)
		result = append(result, u)
		
		for _, v := range graph[u] {
			indegree[v]--
			if indegree[v] == 0 {
				queue = append(queue, v)
			}
		}
	}
	
	if len(result) != N {
		fmt.Println("ERROR")
		return
	}
	
	fmt.Print(strings.Join(formatIntSlice(result), " ") + "\n")
}

func formatIntSlice(slice []int) []string {
	result := make([]string, len(slice))
	for i, v := range slice {
		result[i] = strconv.Itoa(v)
	}
	return result
}