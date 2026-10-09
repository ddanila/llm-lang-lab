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
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	tokens := strings.Fields(input)
	
	if len(tokens) < 2 {
		fmt.Println("ERROR")
		return
	}

	N, _ := strconv.Atoi(tokens[0])
	M, _ := strconv.Atoi(tokens[1])

	if N == 0 && M == 0 {
		fmt.Println()
		return
	}

	indegree := make([]int, N)
	graph := make([][]int, N)

	idx := 2
	for i := 0; i < M; i++ {
		u, _ := strconv.Atoi(tokens[idx])
		v, _ := strconv.Atoi(tokens[idx+1])
		idx += 2
		graph[u] = append(graph[u], v)
		indegree[v]++
	}

	queue := []int{}
	for i := 0; i < N; i++ {
		if indegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := []int{}
	idx2 := 0
	for len(queue) > 0 {
		minVal := queue[0]
		for j := 1; j < len(queue); j++ {
			if queue[j] < minVal {
				minVal = queue[j]
			}
		}
		result = append(result, minVal)
		queue = append(queue[:0], queue[1:]...)
		for _, neighbor := range graph[minVal] {
			indegree[neighbor]--
			if indegree[neighbor] == 0 {
				queue = append(queue, neighbor)
			}
		}
		idx2++
	}

	if len(result) != N {
		fmt.Println("ERROR")
		return
	}

	for i, v := range result {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(v)
	}
	fmt.Println()
}