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
	tokens := strings.Fields(input)
	if len(tokens) < 2 {
		return
	}
	n, _ := strconv.Atoi(tokens[0])
	m, _ := strconv.Atoi(tokens[1])

	if n == 0 {
		fmt.Println("")
		return
	}

	outDegree := make([]int, n)
	inDegree := make([]int, n)
	
	for i := 0; i < m; i++ {
		if len(tokens) <= i+2 {
			break
		}
		u, _ := strconv.Atoi(tokens[i+2])
		v, _ := strconv.Atoi(tokens[i+3])
		
		if u >= n || v >= n {
			continue
		}
		
		outDegree[u]++
		inDegree[v]++
	}

	queue := make([]int, 0)
	for i := 0; i < n; i++ {
		if inDegree[i] == 0 {
			queue = append(queue, i)
		}
	}

	result := make([]int, 0, n)
	idx := 0
	
	for len(queue) > 0 {
		// Find smallest index in queue
		minIdx := -1
		minVal := n + 1
		
		for _, node := range queue {
			if node < minVal {
				minVal = node
				minIdx = idx
			}
			idx++
		}
		
		if minIdx == -1 {
			break
		}
		
		node := queue[minIdx]
		queue = append(queue[:minIdx], queue[minIdx+1:])
		
		result = append(result, node)
		
		for v := 0; v < n; v++ {
			if outDegree[node] > 0 && inDegree[v] > 0 {
				inDegree[v]--
				if inDegree[v] == 0 {
					queue = append(queue, v)
				}
			}
		}
	}

	if len(result) != n {
		fmt.Println("ERROR")
		return
	}

	fmt.Print(result[0])
	for i := 1; i < n; i++ {
		fmt.Printf(" %d", result[i])
	}
	fmt.Println()
}