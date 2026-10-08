package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	var h, w int
	if !scanner.Scan() {
		return
	}
	fields := strings.Fields(scanner.Text())
	h = len(fields[0])
	w = len(fields[1])
	sr, sc, tr, tc := 0, 0, 0, 0
	if len(fields) >= 4 {
		sr, _ = strconv.Atoi(fields[2])
		sc, _ = strconv.Atoi(fields[3])
		tr, _ = strconv.Atoi(fields[4])
		tc, _ = strconv.Atoi(fields[5])
	}

	grid := make([]string, h)
	for i := 0; i < h; i++ {
		if !scanner.Scan() {
			return
		}
		grid[i] = scanner.Text()
	}

	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	if sr == tr && sc == tc {
		fmt.Println("0")
		return
	}

	queue := [][2]int{sr, sc}
	dist := make([][]int, h)
	for i := range dist {
		dist[i] = make([]int, w)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	dist[sr][sc] = 0
	head := 0
	tail := 1

	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	for head < tail {
		x, y := queue[head]
		head++
		d := dist[x][y]
		if d >= 0 && x+dx[0] >= 0 && x+dx[0] < h && y+dy[0] >= 0 && y+dy[0] < w {
			if grid[x+dx[0]][y+dy[0]] == '.' && dist[x+dx[0]][y+dy[0]] == -1 {
				dist[x+dx[0]][y+dy[0]] = d + 1
				queue[tail] = [2]int{x + dx[0], y + dy[0]}
				tail++
			}
		}
		if dist[x][y] >= 0 && x+dx[1] >= 0 && x+dx[1] < h && y+dy[1] >= 0 && y+dy[1] < w {
			if grid[x+dx[1]][y+dy[1]] == '.' && dist[x+dx[1]][y+dy[1]] == -1 {
				dist[x+dx[1]][y+dy[1]] = d + 1
				queue[tail] = [2]int{x + dx[1], y + dy[1]}
				tail++
			}
		}
		if dist[x][y] >= 0 && x+dx[2] >= 0 && x+dx[2] < h && y+dy[2] >= 0 && y+dy[2] < w {
			if grid[x+dx[2]][y+dy[2]] == '.' && dist[x+dx[2]][y+dy[2]] == -1 {
				dist[x+dx[2]][y+dy[2]] = d + 1
				queue[tail] = [2]int{x + dx[2], y + dy[2]}
				tail++
			}
		}
		if dist[x][y] >= 0 && x+dx[3] >= 0 && x+dx[3] < h && y+dy[3] >= 0 && y+dy[3] < w {
			if grid[x+dx[3]][y+dy[3]] == '.' && dist[x+dx[3]][y+dy[3]] == -1 {
				dist[x+dx[3]][y+dy[3]] = d + 1
				queue[tail] = [2]int{x + dx[3], y + dy[3]}
				tail++
			}
		}
	}

	if dist[tr][tc] == -1 {
		fmt.Println("-1")
	} else {
		fmt.Println(dist[tr][tc])
	}
}