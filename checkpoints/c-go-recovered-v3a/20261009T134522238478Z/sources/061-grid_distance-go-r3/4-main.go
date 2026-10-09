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
	parts := strings.Fields(scanner.Text())
	if len(parts) < 6 {
		return
	}
	H, _ := strconv.Atoi(parts[0])
	W, _ := strconv.Atoi(parts[1])
	sr, _ := strconv.Atoi(parts[2])
	sc, _ := strconv.Atoi(parts[3])
	tr, _ := strconv.Atoi(parts[4])
	tc, _ := strconv.Atoi(parts[5])

	grid := make([]string, H)
	for i := 0; i < H; i++ {
		if !scanner.Scan() {
			break
		}
		grid[i] = scanner.Text()
	}

	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}
	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
	}
	for i := 0; i < H; i++ {
		for j := 0; j < W; j++ {
			if grid[i][j] == '.' {
				dist[i][j] = -1
			} else {
				dist[i][j] = 1000000
			}
		}
	}

	queue := make([][]int, H)
	for i := range queue {
		queue[i] = []int{}
	}
	queue[sr] = append(queue[sr], sc)
	dist[sr][sc] = 0

	head := 0
	for head < len(queue[0]) || head < len(queue[1]) || head < len(queue[2]) {
		if head >= H {
			break
		}
		if len(queue[head]) > 0 {
			c := queue[head][0]
			queue[head] = queue[head][1:]
			currDist := dist[head][c]
			for _, nr := range []int{head - 1, head + 1} {
				if nr >= 0 && nr < H && dist[nr][c] == 1000000 {
					dist[nr][c] = currDist + 1
					queue[nr] = append(queue[nr], c)
				}
			}
			for _, nc := range []int{c - 1, c + 1} {
				if nc >= 0 && nc < W && dist[head][nc] == 1000000 {
					dist[head][nc] = currDist + 1
					queue[head] = append(queue[head], nc)
				}
			}
		} else {
			head++
		}
	}

	fmt.Println(dist[tr][tc])
}