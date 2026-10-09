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
		fmt.Println("ERROR")
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

		// Self-loops and duplicate edges are allowed but don't affect topological sort logic
		// However, self-loop u->u means cycle if we consider it strictly.
		// But problem says "duplicate edges and self-edges are allowed" - let's check if self-loop implies cycle.
		// In standard topological sort, a self-loop (u->u) is a cycle.
		// But the problem says they are allowed... Let's re-read: "An edge means u must precede v."
		// If u must precede u, that's always true, but it doesn't create a cycle in the ordering sense.
		// Actually, self-loop would mean u < u which is impossible, so it's a cycle.
		// But the problem says self-edges are allowed. This is ambiguous.
		// Let's assume self-edges are allowed and don't cause ERROR (treated as no constraint).
		if u != v {
			adj[u] = append(adj[u], v)
			inDegree[v]++
		}
	}

	// Kahn's algorithm with min-heap (using sorted list for simplicity since N <= 20)
	// Use a slice as priority queue, always pick smallest available node
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

		// Sort zeroIn to get lexicographically smallest
		// Since we always remove the smallest, we need to maintain order
		// But simpler: just sort each time since N is small (<=20)
		for i := 0; i < len(zeroIn)-1; i++ {
			for j := i + 1; j < len(zeroIn); j++ {
				if zeroIn[j] < zeroIn[i] {
					zeroIn[i], zeroIn[j] = zeroIn[j], zeroIn[i]
				}
			}
		}

		u := zeroIn[0]
		zeroIn = zeroIn[1:]

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