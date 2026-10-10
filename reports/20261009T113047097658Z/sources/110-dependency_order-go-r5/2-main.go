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
		return
	}
	N, _ := strconv.Atoi(tokens[0])
	M, _ := strconv.Atoi(tokens[1])

	if N == 0 {
		fmt.Println()
		return
	}

	inDegree := make([]int, N)
	graph := make([][]int, N)

	for i := 0; i < M; i++ {
		if len(tokens) <= 2+2*i {
			break
		}
		u, _ := strconv.Atoi(tokens[2+2*i])
		v, _ := strconv.Atoi(tokens[3+2*i])
		graph[u] = append(graph[u], v)
		inDegree[v]++
	}

	queue := make([]int, 0)
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := make([]int, 0, N)
	for len(queue) > 0 {
		minVal := queue[0]
		minIdx := 0
		for i := 1; i < len(queue); i++ {
			if queue[i] < minVal {
				minVal = queue[i]
				minIdx = i
			}
		}
		result = append(result, queue[minIdx])
		queue = append(queue[:minIdx], queue[minIdx+1:]...)

		for _, v := range graph[result[len(result)-1]] {
			inDegree[v]--
			if inDegree[v] == 0 {
				queue = append(queue, v)
			}
		}
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