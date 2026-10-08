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

	// Read all input tokens
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)

	if len(tokens) == 0 {
		fmt.Println("")
		return
	}

	N, _ := strconv.Atoi(tokens[0])
	M, _ := strconv.Atoi(tokens[1])

	// For N=0, output empty line
	if N == 0 {
		fmt.Println("")
		return
	}

	// Build adjacency list and in-degree count
	adj := make([][]int, N)
	inDegree := make([]int, N)

	idx := 2
	for i := 0; i < M; i++ {
		if idx+1 >= len(tokens) {
			break
		}
		u, _ := strconv.Atoi(tokens[idx])
		v, _ := strconv.Atoi(tokens[idx+1])
		idx += 2

		// Self-loop u->u creates a cycle (u must precede u is impossible)
		if u == v {
			// Self-loop - this is a cycle
			fmt.Println("ERROR")
			return
		}

		adj[u] = append(adj[u], v)
		inDegree[v]++
	}

	// Kahn's algorithm with lexicographically smallest selection
	var zeroIn []int
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			zeroIn = append(zeroIn, i)
		}
	}

	result := make([]int, 0, N)

	for len(result) < N {
		if len(zeroIn) == 0 {
			// Cycle detected
			fmt.Println("ERROR")
			return
		}

		// Find the smallest node in zeroIn
		minIdx := 0
		for i := 1; i < len(zeroIn); i++ {
			if zeroIn[i] < zeroIn[minIdx] {
				minIdx = i
			}
		}
		u := zeroIn[minIdx]
		zeroIn = append(zeroIn[:minIdx], zeroIn[minIdx+1:]...)

		result = append(result, u)

		for _, v := range adj[u] {
			inDegree[v]--
			if inDegree[v] == 0 {
				zeroIn = append(zeroIn, v)
			}
		}
	}

	fmt.Print(strings.Join(toString(result), " ") + "\n")
}

func toString(arr []int) []string {
	res := make([]string, len(arr))
	for i, v := range arr {
		res[i] = strconv.Itoa(v)
	}
	return res
}