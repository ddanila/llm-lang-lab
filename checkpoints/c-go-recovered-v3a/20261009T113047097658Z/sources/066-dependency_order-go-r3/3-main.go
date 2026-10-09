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
	tokens := []string{}
	for scanner.Scan() {
		tokens = append(tokens, strings.Fields(scanner.Text())...)
	}
	if len(tokens) == 0 {
		return
	}
	n, err := strconv.Atoi(tokens[0])
	if err != nil || n < 0 || n > 20 {
		return
	}
	m, err := strconv.Atoi(tokens[1])
	if err != nil || m < 0 || m > 100 {
		return
	}

	in := make([][]int, n)
	for i := range in {
		in[i] = []int{}
	}

	idx := 2
	for i := 0; i < m; i++ {
		if idx >= len(tokens) {
			break
		}
		u, err := strconv.Atoi(tokens[idx])
		if err != nil {
			break
		}
		v, err := strconv.Atoi(tokens[idx+1])
		if err != nil {
			break
		}
		idx += 2
		if u < n && v < n {
			in[u] = append(in[u], v)
		}
	}

	degree := make([]int, n)
	for _, adj := range in {
		for _, v := range adj {
			degree[v]++
		}
	}

	queue := []int{}
	for i := 0; i < n; i++ {
		if degree[i] == 0 {
			queue = append(queue, i)
		}
	}

	var result []int
	for len(queue) > 0 {
		minVal := queue[0]
		for _, v := range queue[1:] {
			if v < minVal {
				minVal = v
			}
		}
		result = append(result, minVal)

		for _, adj := range in[minVal] {
			degree[adj]--
			if degree[adj] == 0 {
				queue = append(queue, adj)
			}
		}

		newQueue := []int{}
		for _, v := range queue {
			if v != minVal {
				newQueue = append(newQueue, v)
			}
		}
		queue = newQueue
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