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
	fields := strings.Fields(input)
	if len(fields) < 2 {
		return
	}
	N, _ := strconv.Atoi(fields[0])
	M, _ := strconv.Atoi(fields[1])

	if N == 0 && M == 0 {
		fmt.Println()
		return
	}

	in := make([][]int, N)
	out := make([]int, N)
	for i := range in {
		in[i] = nil
		out[i] = 0
	}

	var edgesRead int
	for i := 0; i < M; i++ {
		line, _ := reader.ReadString('\n')
		fields = strings.Fields(line)
		if len(fields) < 2 {
			continue
		}
		u, _ := strconv.Atoi(fields[0])
		v, _ := strconv.Atoi(fields[1])
		if u >= N || v >= N {
			continue
		}
		in[v] = append(in[v], u)
		out[u]++
		edgesRead++
	}

	// Kahn's algorithm with a min-heap simulated by a sorted list
	queue := []int{}
	for i := 0; i < N; i++ {
		if out[i] == 0 {
			queue = append(queue, i)
		}
	}
	// Sort queue to ensure lexicographically smallest order
	sortInts(queue)

	result := []int{}
	for len(queue) > 0 {
		// Pop the smallest element
		minVal := queue[0]
		queue = queue[1:]
		result = append(result, minVal)

		// Decrease out-degree of neighbors
		for _, u := range in[minVal] {
			out[u]--
			if out[u] == 0 {
				queue = append(queue, u)
			}
		}
		// Re-sort queue to maintain lexicographic order
		sortInts(queue)
	}

	if len(result) != N {
		fmt.Println("ERROR")
		return
	}

	fmt.Print(strings.Join(result, " ") + "\n")
}

func sortInts(a []int) {
	for i := 0; i < len(a)-1; i++ {
		for j := i + 1; j < len(a); j++ {
			if a[j] < a[i] {
				a[i], a[j] = a[j], a[i]
			}
		}
	}
}