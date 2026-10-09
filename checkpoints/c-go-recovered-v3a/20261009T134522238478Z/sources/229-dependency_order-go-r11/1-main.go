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

	// If M is given but no edges follow, we need to handle that.
	// The input might have more tokens on subsequent lines.
	for len(tokens) < int(M*2+2) {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		tokens = append(tokens, strings.Fields(line)...)
	}

	// Parse edges
	indegree := make([]int, N)
	graph := make([][]int, N)

	for i := 0; i < M*2+2; i++ {
		if len(tokens) <= i {
			break
		}
		u, err := strconv.Atoi(tokens[i])
		if err != nil || u < 0 || u >= N {
			continue
		}
		v, err := strconv.Atoi(tokens[i+1])
		if err != nil || v < 0 || v >= N {
			i++
			continue
		}
		// Add edge u -> v
		graph[u] = append(graph[u], v)
		indegree[v]++
		i++
	}

	// Kahn's algorithm with a min-heap simulation using sorted list
	// Since N is small (<=20), we can just use a slice and sort it each time.
	queue := make([]int, 0)
	for i := 0; i < N; i++ {
		if indegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	// Sort queue to get lexicographically smallest
	sortSlice(queue)

	result := make([]int, 0, N)
	hasCycle := false

	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]

		result = append(result, u)

		for _, v := range graph[u] {
			indegree[v]--
			if indegree[v] == 0 {
				queue = append(queue, v)
			}
		}
		sortSlice(queue)
	}

	if len(result) < N {
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

func sortSlice(s []int) {
	for i := 0; i < len(s); i++ {
		for j := i + 1; j < len(s); j++ {
			if s[i] > s[j] {
				s[i], s[j] = s[j], s[i]
			}
		}
	}
}