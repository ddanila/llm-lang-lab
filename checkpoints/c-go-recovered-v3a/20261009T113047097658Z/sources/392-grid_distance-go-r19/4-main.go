package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	var H, W, sr, sc, tr, tc int
	fmt.Fscanf(scanner.Buffered(), "%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc)

	grid := make([]string, H)
	for i := 0; i < H; i++ {
		scanner.Scan()
		grid[i] = scanner.Text()
	}

	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	queue := [][2]int{{sr, sc}}
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}
	dist[sr][sc] = 0

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	head := 0
	for head < len(queue) {
		r, c := queue[head]
		head++
		if r == tr && c == tc {
			fmt.Println(dist[r][c])
			return
		}
		d := dist[r][c]
		for k := 0; k < 4; k++ {
			nr, nc := r+dr[k], c+dc[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = d + 1
				queue = append(queue, [2]int{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}