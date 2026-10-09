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

	// Read H W sr sc tr tc
	line1, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields := strings.Fields(line1)
	H, _ := strconv.Atoi(fields[0])
	W, _ := strconv.Atoi(fields[1])
	sr, _ := strconv.Atoi(fields[2])
	sc, _ := strconv.Atoi(fields[3])
	tr, _ := strconv.Atoi(fields[4])
	tc, _ := strconv.Atoi(fields[5])

	// Read grid
	grid := make([][]byte, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimRight(line, "\r\n")
		if len(line) == 0 {
			break
		}
		grid[i] = []byte(line)
	}

	// Validate start and end
	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}

	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS
	queue := [][2]int{{sr, sc}}
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	dist[sr][sc] = 0
	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	head := 0
	for head < len(queue) {
		x, y := queue[head]
		head++

		if x == tr && y == tc {
			fmt.Println(dist[x][y])
			return
		}

		d := dist[x][y]
		for i := 0; i < 4; i++ {
			nx, ny := x+dx[i], y+dy[i]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] != '#' && dist[nx][ny] == -1 {
				dist[nx][ny] = d + 1
				queue = append(queue, [2]int{nx, ny})
			}
		}
	}

	fmt.Println("-1")
}