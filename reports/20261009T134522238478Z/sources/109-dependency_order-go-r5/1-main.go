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
	input, _ := reader.ReadString('\n')
	fields := strings.Fields(input)
	if len(fields) < 2 {
		fmt.Println("ERROR")
		return
	}
	n, err := strconv.Atoi(fields[0])
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	m, err := strconv.Atoi(fields[1])
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	if n == 0 && m == 0 {
		fmt.Println("")
		return
	}

	in := make([][]int, n)
	for i := range in {
		in[i] = make([]int, 0)
	}
	outDegree := make([]int, n)
	for i := 0; i < m; i++ {
		if i+2 >= len(fields) {
			break
		}
		u, err := strconv.Atoi(fields[i+2])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(fields[i+3])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		if u < 0 || u >= n || v < 0 || v >= n {
			fmt.Println("ERROR")
			return
		}
		in[u] = append(in[u], v)
		outDegree[v]++
	}

	queue := make([]int, 0)
	for i := 0; i < n; i++ {
		if outDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := make([]int, 0, n)
	idx := 0
	for len(queue) > 0 {
		minIdx := -1
		minVal := n + 1
		for _, q := range queue {
			if q < minVal {
				minVal = q
				minIdx = idx
			}
		}
		if minIdx == -1 {
			break
		}
		result = append(result, minVal)
		queue = append(queue[:minIdx], queue[minIdx+1:]...)
		idx++

		for _, neighbor := range in[minVal] {
			outDegree[neighbor]--
			if outDegree[neighbor] == 0 {
				queue = append(queue, neighbor)
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