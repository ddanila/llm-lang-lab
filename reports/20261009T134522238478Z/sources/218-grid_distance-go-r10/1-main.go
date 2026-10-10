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

	if !scanner.Scan() {
		return
	}
	line0 := strings.TrimSpace(scanner.Text())
	parts := strings.Fields(line0)
	if len(parts) < 6 {
		return
	}

	H, _ := strconv.Atoi(parts[0])
	W, _ := strconv.Atoi(parts[1])
	sr, _ := strconv.Atoi(parts[2])
	sc, _ := strconv.Atoi(parts[3])
	tr, _ := strconv.Atoi(parts[4])
	tc, _ := strconv.Atoi(parts[5])

	gridLines := make([]string, H)
	for i := 1; i < H+1; i++ {
		if !scanner.Scan() {
			return
		}
		gridLines[i-1] = scanner.Text()
	}

	// Validate start and end points
	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}

	if gridLines[sr][sc] == '#' || gridLines[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	if sr == tr && sc == tc {
		fmt.Println("0")
		return
	}

	// BFS
	queue := [][2]int{}
	distMap := make(map[[2]int]int)
	dir := [][2]int{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}

	queue = append(queue, [2]int{sr, sc})
	distMap[[2]int{sr, sc}] = 0

	head := 0
	for head < len(queue) {
		curr := queue[head]
	head++
		dx, dy := curr[0], curr[1]
		d := distMap[curr]

		for _, delta := range dir {
			nx, ny := dx+delta[0], dy+delta[1]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && gridLines[nx][ny] != '#' {
				if _, ok := distMap[[2]int{nx, ny}]; !ok {
					distMap[[2]int{nx, ny}] = d + 1
					queue = append(queue, [2]int{nx, ny})
				}
			}
		}
	}

	d, ok := distMap[[2]int{tr, tc}]
	if !ok {
		fmt.Println("-1")
	} else {
		fmt.Println(d)
	}
}