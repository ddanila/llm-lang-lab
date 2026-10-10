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
	firstLine := strings.TrimSpace(scanner.Text())
	parts := strings.Fields(firstLine)
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
	for i := 0; i < H; i++ {
		if !scanner.Scan() {
			break
		}
		gridLines[i] = strings.TrimSpace(scanner.Text())
	}

	grid := make([][]byte, H)
	for i := 0; i < H; i++ {
		grid[i] = []byte(gridLines[i])
	}

	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	queue := make([]int, 0)
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	queue = append(queue, sr*W+sc)
	dist[sr][sc] = 0

	head := 0
	for head < len(queue) {
		curr := queue[head]
		head++
		r := curr / W
		c := curr % W
		d := dist[r][c]
		if r == tr && c == tc {
			fmt.Println(d)
			return
		}
		for _, nr := range []int{r - 1, r + 1} {
			if nr >= 0 && nr < H && grid[nr][c] == '.' && dist[nr][c] == -1 {
				dist[nr][c] = d + 1
				queue = append(queue, nr*W+c)
			}
		}
		for _, nc := range []int{c - 1, c + 1} {
			if nc >= 0 && nc < W && grid[r][nc] == '.' && dist[r][nc] == -1 {
				dist[r][nc] = d + 1
				queue = append(queue, r*W+nc)
			}
		}
	}

	if dist[tr][tc] != -1 {
		fmt.Println(dist[tr][tc])
	} else {
		fmt.Println("-1")
	}
}