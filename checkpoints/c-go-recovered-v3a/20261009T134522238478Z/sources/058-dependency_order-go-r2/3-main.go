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

	adj := make([][]int, N)
	inDegree := make([]int, N)
	
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
		adj[u] = append(adj[u], v)
		inDegree[v]++
	}

	// Kahn's algorithm with a min-heap simulated by a sorted list
	queue := []int{}
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}
	sortInts(queue)

	result := []string{}
	for len(queue) > 0 {
		minVal := queue[0]
		queue = queue[1:]
		result = append(result, strconv.Itoa(minVal))

		for _, v := range adj[minVal] {
			inDegree[v]--
			if inDegree[v] == 0 {
				queue = append(queue, v)
			}
		}
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