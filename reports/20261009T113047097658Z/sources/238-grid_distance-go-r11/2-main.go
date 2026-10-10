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

	// Read H and W
	line1, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields := strings.Fields(line1)
	H, _ := strconv.Atoi(fields[0])
	W, _ := strconv.Atoi(fields[1])

	// Read sr, sc, tr, tc
	line2, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields = strings.Fields(line2)
	sr, _ := strconv.Atoi(fields[0])
	sc, _ := strconv.Atoi(fields[1])
	tr, _ := strconv.Atoi(fields[2])
	tc, _ := strconv.Atoi(fields[3])

	// Read grid
	grid := make([][]byte, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimRight(line, "\r\n")
		if len(line) > W {
			line = line[:W]
		} else if len(line) < W {
			line = append(line, make([]byte, W-len(line))...)
		}
		grid[i] = []byte(line)
	}

	// Validate endpoints
	if sr < 0 || sr >= H || sc < 0 || sc >= W || grid[sr][sc] == '#' {
		fmt.Println("-1")
		return
	}
	if tr < 0 || tr >= H || tc < 0 || tc >= W || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	// BFS
	queue := make([][2]int, 0)
	queue = append(queue, [2]int{sr, sc})
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
	}
	dist[sr][sc] = 0
	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		if curr[0] == tr && curr[1] == tc {
			fmt.Println(dist[curr[0]][curr[1]])
			return
		}

		for k := range dr {
			nr, nc := curr[0]+dr[k], curr[1]+dc[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] != '#' && dist[nr][nc] == -1 {
				dist[nr][nc] = dist[curr[0]][curr[1]] + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}