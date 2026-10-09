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
	n, _ := strconv.Atoi(tokens[0])
	m, _ := strconv.Atoi(tokens[1])

	if n == 0 && m == 0 {
		fmt.Println()
		return
	}

	adj := make([][]int, n)
	inDegree := make([]int, n)
	for i := 0; i < m; i++ {
		if len(tokens) > 2+i*2 {
			u, _ := strconv.Atoi(tokens[2+i*2])
			v, _ := strconv.Atoi(tokens[3+i*2])
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}

	queue := make([]int, 0)
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := make([]int, 0, n)

	for len(queue) > 0 {
		i := queue[0]
		queue = queue[1:]
		result = append(result, i)
		for _, v := range adj[i] {
			inDegree[v]--
			if inDegree[v] == 0 {
				queue = append(queue, v)
			}
		}
	}

	if len(result) != n {
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