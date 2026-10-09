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

	inDegree := make([]int, N)
	graph := make([][]int, N)

	for i := 0; i < M; i++ {
		line, err := reader.ReadString('\n')
		if err != nil || len(line) == 0 {
			break
		}
		fields = strings.Fields(line)
		if len(fields) < 2 {
			continue
		}
		u, _ := strconv.Atoi(fields[0])
		v, _ := strconv.Atoi(fields[1])
		graph[u] = append(graph[u], v)
		inDegree[v]++
	}

	var result []int
	pq := make([]int, 0, N)
	for i := 0; i < N; i++ {
		if inDegree[i] == 0 {
			pq = append(pq, i)
		}
	}

	idx := 0
	for len(pq) > 0 {
		smallest := pq[0]
		for i := 1; i < len(pq); i++ {
			if pq[i] < smallest {
				smallest = pq[i]
			}
		}
		result = append(result, smallest)
		idx++
		pq = removeElement(pq, smallest)

		for _, neighbor := range graph[smallest] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				pq = append(pq, neighbor)
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

func removeElement(slice []int, val int) []int {
	newSlice := make([]int, 0, len(slice)-1)
	for _, v := range slice {
		if v != val {
			newSlice = append(newSlice, v)
		}
	}
	return newSlice
}