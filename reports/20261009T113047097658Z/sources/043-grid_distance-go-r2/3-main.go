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

	var h, w int
	if !scanner.Scan() {
		return
	}
	fields := strings.Fields(scanner.Text())
	h, _ = strconv.Atoi(fields[0])
	w, _ = strconv.Atoi(fields[1])
	sr, _ = strconv.Atoi(fields[2])
	sc, _ = strconv.Atoi(fields[3])
	tr, _ = strconv.Atoi(fields[4])
	tc, _ = strconv.Atoi(fields[5])

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

	queue := make([][2]int, 0, h*w)
	dist := make([][]int, h)
	for i := range dist {
		dist[i] = make([]int, w)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	dist[sr][sc] = 0
	queue = append(queue, [2]int{sr, sc})
	head := 0
	tail := 1

	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	for head < tail {
		x, y := queue[head]
		head++
		d := dist[x][y]
		for k := 0; k < 4; k++ {
			nx := x + dx[k]
			ny := y + dy[k]
			if nx >= 0 && nx < h && ny >= 0 && ny < w {
				if grid[nx][ny] == '.' && dist[nx][ny] == -1 {
					dist[nx][ny] = d + 1
					queue = append(queue, [2]int{nx, ny})
					tail++
				}
			}
		}
	}

	if dist[tr][tc] == -1 {
		fmt.Println("-1")
	} else {
		fmt.Println(dist[tr][tc])
	}
}