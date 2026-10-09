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
	var tokens []string
	for scanner.Scan() {
		tokens = append(tokens, strings.Split(scanner.Text(), " ")...)
	}
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}

	n, err := strconv.Atoi(tokens[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	m, err := strconv.Atoi(tokens[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	if n == 0 && m == 0 {
		fmt.Println("")
		return
	}

	inDegree := make([]int, n)
	graph := make([][]int, n)

	for i := 2; i < len(tokens); i += 2 {
		u, err := strconv.Atoi(tokens[i])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(tokens[i+1])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		if u < 0 || u >= n || v < 0 || v >= n {
			fmt.Println("ERROR")
			return
		}
		inDegree[v]++
		graph[u] = append(graph[u], v)
	}

	result := make([]int, 0, n)
	for i := range result {
		result[i] = -1
	}

	queue := make([]int, 0)
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	idx := 0
	for len(queue) > 0 {
		// Find the smallest index node with inDegree 0
		minNode := -1
		for _, node := range queue {
			if minNode == -1 || node < minNode {
				minNode = node
			}
		}
		if minNode == -1 {
			break
		}

		result = append(result, minNode)
		queue = removeElement(queue, minNode)

		for _, neighbor := range graph[minNode] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				queue = append(queue, neighbor)
			}
		}
	}

	if len(result) != n {
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

func removeElement(slice []int, val int) []int {
	newSlice := make([]int, 0, len(slice))
	for _, v := range slice {
		if v != val {
			newSlice = append(newSlice, v)
		}
	}
	return newSlice
}