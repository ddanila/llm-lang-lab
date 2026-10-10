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

	if N == 0 && M == 0 {
		fmt.Println("")
		return
	}

	in := make([][]int, N)
	outDegree := make([]int, N)
	tokenIdx := 2
	for i := 0; i < M; i++ {
		if tokenIdx+1 >= len(tokens) {
			break
		}
		u, _ := strconv.Atoi(tokens[tokenIdx])
		v, _ := strconv.Atoi(tokens[tokenIdx+1])
		if u >= N || v >= N {
			continue
		}
		in[v] = append(in[v], u)
		outDegree[u]++
		tokenIdx += 2
	}

	queue := make([]int, 0)
	for i := 0; i < N; i++ {
		if outDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := make([]int, 0)
	for len(queue) > 0 {
		minVal := -1
		for _, val := range queue {
			if minVal == -1 || val < minVal {
				minVal = val
			}
		}
		result = append(result, minVal)

		for _, neighbor := range in[minVal] {
			outDegree[neighbor]--
			if outDegree[neighbor] == 0 {
				queue = append(queue, neighbor)
			}
		}
	}

	if len(result) != N {
		fmt.Println("ERROR")
		return
	}

	for i := 0; i < N; i++ {
		fmt.Print(result[i])
		if i < N-1 {
			fmt.Print(" ")
		}
	}
	fmt.Println()
}