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
	idx := 2
	for i := 0; i < m; i++ {
		if idx+1 >= len(fields) {
			break
		}
		u, err := strconv.Atoi(fields[idx])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		v, err := strconv.Atoi(fields[idx+1])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		if u < 0 || u >= n || v < 0 || v >= n {
			fmt.Println("ERROR")
			return
		}
		// Only add edge if not already present (handle duplicates)
		found := false
		for _, neighbor := range in[u] {
			if neighbor == v {
				found = true
				break
			}
		}
		if !found {
			in[u] = append(in[u], v)
			outDegree[v]++
		}
		idx += 2
	}

	queue := make([]int, 0)
	for i := 0; i < n; i++ {
		if outDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := make([]int, 0, n)
	for len(queue) > 0 {
		minVal := queue[0]
		minIdx := 0
		for qIdx := 1; qIdx < len(queue); qIdx++ {
			if queue[qIdx] < minVal {
				minVal = queue[qIdx]
				minIdx = qIdx
			}
		}
		result = append(result, minVal)
		queue = append(queue[:minIdx], queue[minIdx+1:]...)

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